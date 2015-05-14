
#ifndef PIXEL
#define PIXEL

typedef struct{
    unsigned char rgb[3];   
} Pixel;  

#endif


#ifndef IMAGE
#define IMAGE

class Source;

class Image{

private:
    int width;
    int height;
    Pixel *data;


public:
    
    Source *mySource;
    Image(void);
    Image(Image &);
    Image(int , int );


    Pixel * get_data() const ;
    int get_width() const ;
    void set_size(int, int);
    int get_height() const ;
    void Update() const ;
    void SetSource(Source *);


};

#endif