#include "vga.h"

int col=0;
int row=0;
int line=0;

uint16_t* const vga=(uint16_t* const) 0xB8000;

unsigned short blank;
unsigned char default_color= MAKE_COLOR(LIGHT_GRAY, BLACK) ;




unsigned short makeEntry(unsigned char c, unsigned char color){
 return (unsigned short) c | ((unsigned short) color << 8);
}


 void reSet(){
    row=0;
    col=0;

    for(int r=0;r<height;r++){
        for(int c=0;c<width;c++){
            vga[r*width+c] =makeEntry(' ',default_color);
        }
    }
 }

 void newLine(){
    if(line < height-1){
        line++;
        col=0;
    }else{
        scrollUp();
        col=0;
    }
 }
 void scrollUp(){
    for (int r = 1; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            vga[(r-1)*width + c] = vga[r*width+c];
        }
        for (int c = 0; c < width; c++)
        {
            vga[(height-1) * width + c] = makeEntry(' ',default_color);
        }
        if(line>0) line--;
        
    }
    
 }


 void print(const char* s){
        while(*s){
            switch (*s)
            {
            case '\n':
                newLine();
                break;
            
            case '\r':
                col=0;
                break;
            
                
            default:
                if(col==width){
                   newLine();

                }
                vga[row*width+col] = makeEntry(*s,default_color);
                col++;
                break;
            }
            s++;
        }
    }
