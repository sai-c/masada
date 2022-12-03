# masada

### Team Members
Shivansh Srivastava (SS5945), Sai Chintalapati (VHC2109), Daniel Hu (DH3116)

### Description
In today’s increasingly digital world, billions of people trust their personal data to be stored safely and securely on their computer systems. However, personal data is a valuable target to criminals and attackers, who seek to craft malicious computer programs to induce harm on one’s computer. Thus, antivirus software is prevalent, and is responsible for keeping computer systems safe by scanning for malicious files or software on a machine; in the case that an unwanted program or file is detected, the antivirus software often quarantines the malware safely in a vault, by deactivating it and storing it in case the user wants to recover the program or file. On request by the user, the malicious file is then deleted. 
For the final project, we propose the creation of a high-performance antivirus software for Linux-based systems using C++. Antivirus software works to detect malicious software by utilizing a couple of different methods. Firstly, the fastest method of detecting viruses is comparing files with hashes of well-known malicious files in a database. These databases are updated regularly to keep up with the ever-evolving techniques of attackers. A slower technique, pattern matching can also be utilized to detect the signatures of malicious code within an executable, which are known sequences of bytes associated with malicious code; this search can be sped up using algorithms such as Rabin-Karp. Lastly, behavioral/heuristic analysis can be done to monitor the actions of the program, such as by detecting the files that the process is accessing; if a process is modifying its one file or other executable files, for example, that is considered suspicious activity (How antivirus works? 2018). 

### Goals
- In Version 0.8, the antivirus is to be implemented, including the “quick scan” feature, which includes the scanning of files in the filesystem, hashing them utilizing a fast hashing algorithm such as MD5, and comparing the hashes to the stored hashes of known malicious files. Once a virus is detected, it is deleted. 
- In Version 1.0, more complex virus detection by using full-file pattern-matching should be implemented, searching for any known virus signatures within the files of the system; this can be implemented efficiently by utilizing the Rabin-Karp or KMP algorithms. 
- In Version 1.2, the quarantining feature should be implemented, which entails modifying some bytes of the file to disable its execution, and storing it in a vault. A possible further improvement could also be to implement a simple UI using Qt, which has options of running a quick or deep scan, as well as viewing files in the vault and choosing to delete or quarantine them.

### Testing
The antivirus software will be thoroughly tested by adding to the store hashes or signatures of files, and running the antivirus to determine if it detects the files deemed to be malicious. Unit tests will also be implemented using CTest and dependency injection, where required. The antivirus software can also be benchmarked, to see how many bytes of files it can scan through per time interval (e.g. seconds). 

### Data/input
The only data required by the antivirus program are hashes of malicious files and signatures of malicious parts of files. For testing purposes, files purpose-made can be deemed as malicious, without the use of actual malware. The MD5 hashes of actual malware can be found on virusshare.com, if needed.
Expectations for final presentation: The final presentation will be an overview of the architecture of the antivirus software, and the techniques it utilizes to detect malware on a computer system. The algorithms utilized, and the design decisions made will be discussed in depth. The presentation will also contain a demonstration of the antivirus software detecting and deleting/quarantining proclaimed malware. 
