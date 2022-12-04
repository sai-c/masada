#include "FileVault.h"

FileVault::FileVault(std::string fileName)
{
    this->archive_name = fileName;
    std::ifstream cur_file(this->archive_name, std::ios::binary | std::ios::ate);
    if (cur_file.is_open())
    {
        std::streampos file_size = cur_file.tellg();
        cur_file.seekg(0, std::ios::beg);
        std::vector<char> magic(8);
        cur_file.read(magic.data(), 8);
        if (this->magic.compare(std::string(magic.data(), 8)))
        {
            perror("not an archive");
            return;
        }
        int num_files;
        cur_file.read((char *)&num_files, 4);
        for (int i = 0; i < (long long)num_files; i++)
        {
            std::string filename = std::string(20, '\0');
            cur_file.read(&filename[0], 20);
            long unsigned int filesize;
            cur_file.read((char *)&filesize, 8);
            std::vector<char> data(filesize);
            cur_file.read(data.data(), filesize);
            File cur_file = {
                filename,
                filesize,
                data,
            };
            this->files.push_back(cur_file);
        }
    }
}

std::vector<std::string> FileVault::list()
{
    std::vector<std::string> fileNames;
    for (File file : this->files)
    {
        fileNames.push_back(file.filename);
    }
    return fileNames;
}

void FileVault::extract(std::string file_str)
{
    bool exists = false;
    for (File file : this->files)
    {
        if (strcmp(file_str.c_str(), file.filename.c_str()) == 0)
        {
            exists = true;
            std::ofstream ofs(file.filename, std::ofstream::binary | std::ofstream::trunc);
            ofs.write(file.data.data(), file.data.size());
            ofs.close();
        }
    }
    if (exists == false)
    {
        perror("a file doesn't exist in the archive");
        return;
    }
}

void FileVault::remove(std::vector<std::string> files)
{
    long long init_num = this->files.size();
    auto deleteFiles = [&](File file) -> bool
    {
        for (std::string file_str : files)
        {
            if (strcmp(file_str.c_str(), file.filename.c_str()) == 0)
            {
                return true;
            }
        }

        return false;
    };
    auto iterator = std::remove_if(this->files.begin(), this->files.end(), deleteFiles);
    this->files.erase(iterator, this->files.end());
    if (init_num - this->files.size() != files.size())
    {
        std::cout << this->files.size();
        std::cout << init_num;
        std::cout << files.size();
        perror("file doesn't exist in the archive");
        return;
    }
    this->change = true;
}

void FileVault::add(std::string file_name)
{
    for (File f : this->files)
    {
        if (strcmp(file_name.c_str(), f.filename.c_str()) == 0)
        {
            perror("file already exists");
            return;
        }
    }

    std::ifstream openfile(file_name, std::ios::binary | std::ios::ate);
    std::vector<char> data_to_write;

    if (openfile.is_open())
    {
        std::streampos file_size = openfile.tellg();
        if (file_size == 0)
        {
            perror("file is empty");
            return;
        }
        data_to_write.resize(file_size);
        openfile.seekg(0, std::ios::beg);
        openfile.read((char *)data_to_write.data(), file_size);
        openfile.close();
        openfile.close();
    }
    else
    {
        perror("error opening file");
        return;
    }
    std::string padded_file_name = file_name;
    padded_file_name.insert(file_name.size(), 20 - file_name.size(), 0);

    File cur_file = {
        padded_file_name,
        data_to_write.size(),
        data_to_write,
    };
    this->files.push_back(cur_file);
    this->change = true;
}

FileVault::~FileVault()
{
    if (this->change)
    {
        if (this->files.size() == 0)
        {
            if (std::remove(this->archive_name.data()) != 0)
                perror("Error deleting file");
            return;
        }
        std::ofstream ofs(this->archive_name, std::ofstream::binary | std::ofstream::trunc);

        ofs.write(this->magic.c_str(), 8);
        long long num_files = this->files.size();
        ofs.write((char *)&num_files, 4);
        for (File file : this->files)
        {
            ofs.write(file.filename.c_str(), 20);
            ofs.write((char *)&file.filesize, 8);
            ofs.write(file.data.data(), file.data.size());
        }
        ofs.close();
    }
}
