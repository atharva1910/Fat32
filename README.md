# A very simple implemetation of FAT32 filesystem

##written in C++

HardDisk layout:

512 Bytes -> File Tables


  File Tables:
  
    Name.
    Position.
    Size.
    
    
256 Bytes -> FreeSpace Bitmap


  FreeSpace:
  
    Position.
    Size.
    
####TODO:
  Delete entry.
  Combine Free Spaces.
    
