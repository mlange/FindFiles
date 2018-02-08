#define _WIN32_WINNT  0x0400

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int main(int argc, char *argv[]) 
{

    HANDLE hFile; 	
    DWORD count = 1; 
    WIN32_FIND_DATA Win32Data; 	

    if (argc != 2) 
    {
        printf("Usage: %s <filename(accepts wildcards)>\n", argv[0]); 
        return 0; 
    }  	

    hFile = FindFirstFileEx(argv[1], FindExInfoStandard,
                            (LPVOID) &Win32Data,
                            FindExSearchNameMatch, 
                            NULL, 0); 

    if (hFile == INVALID_HANDLE_VALUE)
    { 	
        fprintf(stderr, "Could not find first file: Error code %d\n",
        GetLastError( )); 	
        return -1; 
    } 
    
    do 
    { 	
        printf("File #%d: %s\n", count++, Win32Data.cFileName);
        
        switch (Win32Data.dwFileAttributes) 
        { 
        case FILE_ATTRIBUTE_DIRECTORY: 	
            printf("Directory\n"); 		
            break; 		
        case FILE_ATTRIBUTE_NORMAL: 
            printf("Normal file\n"); 
            break; 		
        case FILE_ATTRIBUTE_SYSTEM: 
            printf("System file\n"); 
            break; 		
        case FILE_ATTRIBUTE_ARCHIVE: 		
            printf("Archived file\n"); 		
            break; 	
        default: 		
            printf("Other type of file\n"); 
            break; 	
        }  	
        
       _getch( ); 	

    } while (FindNextFile(hFile, &Win32Data)); 

    FindClose(hFile);

    exit(0);
}
