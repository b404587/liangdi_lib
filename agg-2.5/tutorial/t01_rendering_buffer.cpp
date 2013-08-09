#include <stdio.h>
#include <cstring>
#include "agg_rendering_buffer.h"

enum
{
    frame_width = 640,//320,
    frame_height = 400//200
};

// Writing the buffer to a .PPM file, assuming it has 
// RGB-structure, one byte per color component
//--------------------------------------------------
bool write_ppm(const unsigned char* buf, 
               unsigned width, 
               unsigned height, 
               const char* file_name)
{
    FILE* fd = fopen(file_name, "wb");
    if(fd)
    {
        fprintf(fd, "P6 %d %d 255 ", width, height);
        fwrite(buf, 1, width * height * 3, fd);
        fclose(fd);
        return true;
    }
    return false;
}

// Draw a black frame around the rendering buffer, assuming it has 
// RGB-structure, one byte per color component
//--------------------------------------------------
void draw_black_frame(agg::rendering_buffer& rbuf)
{
    unsigned i;
    for(i = 0; i < rbuf.height(); ++i)
    {
        unsigned char* p = rbuf.row_ptr(i);
        *p++ = 0; *p++ = 0; *p++ = 0;

	*(p+21) = 127;*(p+22) = 200;*(p+23) = 98;
		
        p += (rbuf.width() - 2) * 3;
        *p++ = 0; *p++ = 0; *p++ = 0;
    }
    memset(rbuf.row_ptr(0), 0, rbuf.width() * 3);
    memset(rbuf.row_ptr(rbuf.height() - 1), 0, rbuf.width() * 3);
}


int main()
{
    // In the first example we do the following:
    //--------------------
    // Allocate the buffer.
    // Clear the buffer, for now "manually"
    // Create the rendering buffer object
    // Do something simple, draw a diagonal line
    // Write the buffer to agg_test.ppm
    // Free memory

    unsigned char* buffer = new unsigned char[frame_width * frame_height * 3];

    memset(buffer, 255, frame_width * frame_height * 3);

    agg::rendering_buffer rbuf(buffer, 
                               frame_width, 
                               frame_height, 
                               frame_width * 3);

//    agg::rendering_buffer rbuf(buffer, 
//                               frame_width, 
//                               frame_height, 
//                               -frame_width * 3);

	draw_black_frame(rbuf);

//	rbuf.attach(buffer + 
//			  frame_width * 3 * 20 +	  // initial Y-offset
//			  3 * 20,					  // initial X-offset
//			frame_width - 40,
//			frame_height - 40,
//			frame_width * 3 			  // Note that the stride
//										  // remains the same
//			);

	rbuf.attach(buffer + 
		  frame_width * 3 * 20 +	  // initial Y-offset
		  3 * 20,					  // initial X-offset
		frame_width - 40,
		frame_height - 40,
		-frame_width * 3 			  // Note that the stride
									  // remains the same
		);

    unsigned i;
    for(i = 0; i < rbuf.height()/2; ++i)
    {
        // Get the pointer to the beginning of the i-th row (Y-coordinate)
        // and shift it to the i-th position, that is, X-coordinate.
        //---------------
        unsigned char* ptr = rbuf.row_ptr(i) + i * 3;
        
        // PutPixel, very sophisticated, huh? :)
        //-------------
        *ptr++ = 127; // R
        *ptr++ = 200; // G
        *ptr++ = 98;  // B
    }

    draw_black_frame(rbuf);
    write_ppm(buffer, frame_width, frame_height, "agg_test.ppm");

    delete [] buffer;
    return 0;
}

