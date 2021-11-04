#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>

using namespace std;
int main(int argc, char** argv)
{
  
    	if(argc < 3)
    	{
      		cerr << "No source and destination files" << endl;
      		exit(1);
    	}	
  
    	const char* sourcePath = argv[1];
    	int source = open(sourcePath, O_RDONLY);
  
    	if(source < 0)
    	{
      		cerr << "ERROR " << errno << endl;
      		exit(errno);    
    	}
  
    	const char* destinationPath = argv[2];
    	int destination = open(destinationPath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);
  
    	if(destination < 0)
    	{
        	cerr << "ERROR " << errno << endl;
        	exit(errno);    
    	}
    
    	off_t logicalSizeOfSource = lseek(source, 0, SEEK_END);
  
    	if(logicalSizeOfSource < 0)
    	{
      		cerr << "Seek Error" << endl;
      		exit(errno);
   	}
  
    	cout << "Logical size of source file " << logicalSizeOfSource << endl;
  
    	off_t holeOfSource = 0;
    	size_t physicalSizeOfSource = 0;
    	size_t sizeOfHoles = 0;
    
    	//get the physical size of source file
	while(sizeOfHoles + physicalSizeOfSource != logicalSizeOfSource)
    	{
      		off_t dataOfSource = lseek(source, holeOfSource, SEEK_DATA);
      		
		if(dataOfSource < 0)
      		{
        	std::cerr << "Seek Error" << std::endl;
        	exit(errno);
      		}

     		 off_t holeAmount = dataOfSource - holeOfSource;
      		holeOfSource = lseek(source, dataOfSource, SEEK_HOLE);

      		if(holeOfSource < 0)
       		{
            		cerr << "Seek Error" << endl;
            		exit(errno);
        	}

      		if(holeAmount > 0)
      		{
        		sizeOfHoles += holeAmount;
      		}

      		off_t dataAmount = holeOfSource - dataOfSource;
        
                if(dataAmount > 0)
                {
                	physicalSizeOfSource += dataAmount;
        	}
        }
  
        cout << "Physical size = " << physicalSizeOfSource << endl;

        off_t holeOfDestination = 0;
        off_t logicalSizeOfDestination = 0;
        size_t physicalSizeOfDestination = 0;
    
        //start copying file
        while(true)
        {
        	off_t dataOfDestination = lseek(source, holeOfDestination, SEEK_DATA);
      
        	if(dataOfDestination < 0)
        	{
        		cerr << "Seek Error" << endl;
        		exit(errno);
       	 	}
    
        	off_t holeAmount = dataOfDestination - holeOfDestination;

        	if(holeAmount > 0)
        	{ 
        		logicalSizeOfDestination = lseek(destination, holeAmount, SEEK_END);
        	}

        	if(logicalSizeOfSource == logicalSizeOfDestination)
        	{	
        		break;
        	}   

        	holeOfDestination = lseek(source, dataOfDestination, SEEK_HOLE);
    
        	if(holeOfDestination < 0)
        	{
			cerr << "Seek Error" << endl;
                	exit(errno);
        	}
    
        	off_t dataAmount = holeOfDestination - dataOfDestination;
        
        	//copy data from source to destination file
        	if(dataAmount > 0)
        	{
        		char* buffer = new char[dataAmount + 1];
        		dataOfDestination = lseek(source, dataOfDestination, SEEK_SET);
            
        	if(dataOfDestination < 0)
        	{
                	cerr << "Seek Error" << endl;
        		exit(errno);
        	}

        	int readBytes = read(source, buffer, dataAmount);

        	if(readBytes < 0)
        	{
                	cerr << "ERROR " << errno << endl;
                	exit(errno);
        	}

        	int writeBytes = write(destination, buffer, readBytes);
    
        	if(writeBytes < 0)
        	{
                	cerr << "ERROR " << errno << endl;
			exit(errno);
        	}

        	delete [] buffer;
        	physicalSizeOfDestination += dataAmount;
        	logicalSizeOfDestination = lseek(destination, 0, SEEK_END);
		
		if(logicalSizeOfDestination < 0)
            	{
                	cerr << "Seek Error" << endl;
                	exit(errno);
            	}
  
          	if(logicalSizeOfSource == logicalSizeOfDestination)
          	{
                	break;
            	}
      	}
}
  
    	cout << "Logical size of destination file  " << logicalSizeOfDestination << endl;
	cout << "Physical size of destination file " << physicalSizeOfDestination << endl;
  
    	int closeSource = close(source);
  
    	if(closeSource < 0)
    	{
     		 cerr << "ERROR" << endl;
      		exit(errno);
    	}	

    	int closeDestination = close(destination);
  
    	if(closeDestination < 0)
    	{
        	cerr << "ERROR" << endl;
        	exit(errno);
    	}

    return 0;
}
