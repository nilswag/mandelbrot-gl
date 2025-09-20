#version 460 core

out vec4 color;

#define MAX_ITERATIONS 500
 
int getIterations()
{
    float real = (gl_FragCoord.x / 1080.0 - 0.5) * 4.0;
    float imag = (gl_FragCoord.y / 1080.0 - 0.7) * 4.0;
 
    int iterations = 0;
    float constReal = real;
    float constImag = imag;
 
    while (iterations < MAX_ITERATIONS)
    {
        float tmpReal = real;
        real = (real * real - imag * imag) + constReal;
        imag = (2.0 * tmpReal * imag) + constImag;
         
        float dist = real * real + imag * imag;
         
        if (dist > 4.0)
        break;
 
        ++iterations;
    }
    return iterations;
}

vec4 returnColor()
{
    int iter = getIterations();
    if (iter == MAX_ITERATIONS)
    {
        gl_FragDepth = 0.0f;
        return vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
 
    float iterations = float(iter) / MAX_ITERATIONS;    
    return vec4(0.0f, iterations, 0.0f, 1.0f);
}
 
void main()
{
    color = returnColor();
}