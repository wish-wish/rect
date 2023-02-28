#include <stdio.h>
#include <iostream>
#include <functional>
#include <string.h>
#include <math.h>
#include <stdio.h>

//for rectangle

using namespace std;

#define len 100 

void getCenter(int data[len][len],int width,int height,int &pstart,int &pend,int &edgecount)
{
    int diff=width-height;
    if(diff<0)
    {
        int xs=(width-1)/2;
        int ys=(width-1)/2;
        
        int xe=(width-1)/2+(width-1)%2;
        int ye=(width-1)/2+abs(diff)+(width-1)%2;
        pstart=ys*width+xs;
        pend=ye*width+xe;
    }
    else
    {
        int xs=(height-1)/2;
        int ys=(height-1)/2;
        
        int xe=(height-1)/2+abs(diff)+(height-1)%2;
        int ye=(height-1)/2+(height-1)%2;
        pstart=ys*width+xs;
        pend=ye*width+xe;
    }
    edgecount= ((width>height?height:width)-1)/2;
}

int rectangleWalkOut(int data[len][len],int width,int height)
{
    int dindex=1;
    int pstart,pend,edgecount;
    getCenter(data,width,height,pstart,pend,edgecount);
    int startx=pstart/width;
    int starty=pstart%width;
    int endx=pend/width;
    int endy=pend%width;
    //cout<<"pstart="<<pstart<<" pend="<<pend<<" coord:"<<startx<<":"<<starty<<";"<<endx<<":"<<endy<<":"<<edgecount<<endl;
    if(startx==endx&&starty==endy)//middle point
    {
        data[startx][starty]=dindex++;
        data[startx][starty-1]=dindex++; //fill for not top start
        startx--;
        starty--;
        endx++;
        endy++;
    }
    else if(startx==endx)//middle horizonal line
    {
        for(int i=starty;i<=endy+1;i++)//middle line
            data[startx][endy-i+starty]=dindex++;
        startx--;
        starty--;
        endx++;
        endy++;
    }
    else if(starty==endy)//middle vertical line
    {
        for(int i=startx;i<=endx;i++)//middle line
            data[i][starty]=dindex++;
        for(int i=startx;i<=endx;i++)//fill for not top start 
            data[endx-i+startx][starty-1]=dindex++;
        startx--;
        starty--;
        endx++;
        endy++;
    }
    while(edgecount>=0)//middle box
    {
        int i=starty;
        while(i<=endy)//top
        {
            data[startx][i]=dindex++;
            i++;
        }
        i=startx+1;
        while(i<=endx)//right
        {
            data[i][endy]=dindex++;
            i++;
        }
        i=starty+1;
        while(i<=endy+1)//bottom
        {
            data[endx][endy-i+starty]=dindex++;
            i++;
        }
        i=startx+1;
        while(i<=endx)//left
        {
            data[endx-i+startx][starty-1]=dindex++;
            i++;
        }
        startx--;
        starty--;
        endx++;
        endy++;
        edgecount--;
    }
	return 0;
}

void getCenterSquare(int data[len][len],int width,int height,int &pstart,int &pend,int &edgecount)
{
    int diff=width-height;
    int iwidth=width-1,iheight=height-1;
    int xs=iwidth/2;
    int ys=iheight/2;
    int xe=iwidth/2+iwidth%2;
    int ye=iheight/2+iheight%2;
    if(diff>0)
        edgecount=iheight/2-(iheight%2==0?1:0);
    else
        edgecount=iwidth/2-(iwidth%2==0?1:0);
    pstart=ys*width+xs;
    pend=ye*width+xe;
}

void walkCenterSquare(int data[len][len],int width,int height,int borderlen=1)
{
    int dindex=1;
    int pstart,pend,edgecount;
    getCenterSquare(data,width,height,pstart,pend,edgecount);
    int startx=pstart/width;
    int starty=pstart%width;
    int endx=pend/width;
    int endy=pend%width;
    cout<<"pstart="<<pstart<<" pend="<<pend<<" coord:"<<startx<<":"<<starty<<";"<<endx<<":"<<endy<<":"<<edgecount<<endl;
    if(startx==endx&&starty==endy)//middle point
    {
        data[startx][starty]=dindex++;
        data[startx][starty-1]=dindex++; //fill for not top start
        startx--;
        starty--;
        endx++;
        endy++;
    }
    edgecount=edgecount-borderlen;
    while(edgecount>=0)//middle box
    {
        int i=starty;
        while(i<=endy)//top
        {
            data[startx][i]=dindex++;
            i++;
        }
        i=startx+1;
        while(i<=endx)//right
        {
            data[i][endy]=dindex++;
            i++;
        }
        i=starty+1;
        while(i<=(edgecount>0?endy+1:endy))//bottom
        {
            data[endx][endy-i+starty]=dindex++;
            i++;
        }
        i=startx+1;
        while(i<=endx&&edgecount>0)//left
        {
            data[endx-i+startx][starty-1]=dindex++;
            i++;
        }
        startx--;
        starty--;
        endx++;
        endy++;
        edgecount--;
    }
}

int rectangleClockwiseWalkIn(int data[len][len],int width,int height,int edgelen=-1)
{
    int dindex=1;
    int ix=0,iy=0;
    int start=0,endw=width,endh=height;
    if(edgelen==-1)
        edgelen=ceil(endw/2.f);
    while(start<endw&&edgelen>0)
    {
        for(int i=start;i<endw;i++)//top
            if(data[start][i]==0)
                data[start][i]=dindex++;
        endw--;
        endh--;
        for(int i=start;i<endh;i++)//right
            if(data[i+1][endw]==0)
                data[i+1][endw]=dindex++;
        for(int i=start;i<endw;i++)//bottom
            if(data[endh][endw-i+start-1]==0)
                data[endh][endw-i+start-1]=dindex++;
        for(int i=start+1;i<endh;i++)//left
            if(data[endh-i+start][start]==0)
                data[endh-i+start][start]=dindex++;
        start++;
        edgelen--;
    }
	return 0;
}

int rectangleAntiClockwiseWalkIn(int data[len][len],int width,int height,int edgelen=-1)
{
    int dindex=1;
    int ix=0,iy=0;
    int start=0,endw=width,endh=height;
    if(edgelen==-1)
        edgelen=ceil(endw/2.f);
    while(start<endw&&edgelen>0)
    {
        for(int i=start;i<endh;i++)//left
            if(data[i][start]==0)
                data[i][start]=dindex++;
        endh--;
        endw--;
        for(int i=start;i<endw;i++)//bottom
            if(data[endh][i+1]==0)
                data[endh][i+1]=dindex++;
        for(int i=start;i<endh;i++)//right
            if(data[endh-i+start-1][endw]==0)
                data[endh-i+start-1][endw]=dindex++;
        for(int i=start+1;i<endw;i++)//top
            if(data[start][endw-i+start]==0)
                data[start][endw-i+start]=dindex++;
        start++;
        edgelen--;
    }
	return 0;
}

int rectNumber(int awidth,int aheight,int mode,int border=1)
{
    int data[len][len];
    for(int i=0;i<awidth*aheight;i++)
        data[i/awidth][i%awidth]=0;
    if(mode==0)
        rectangleWalkOut(data,awidth,aheight);
    else if(mode==1)
        rectangleClockwiseWalkIn(data,awidth,aheight);
    else if(mode==2)
        rectangleAntiClockwiseWalkIn(data,awidth,aheight);
    else if(mode==3)
        walkCenterSquare(data,awidth,aheight,border);
    cout.flags(ios::internal);
    for(int i=0;i<aheight;i++)
    {
        for(int j=0;j<awidth;j++)
            //cout<<"\t"<<data[i][j];
            printf("%-5d",data[i][j]);
        cout<<endl;
    }
	return 0;
}

int main()
{
    int awidth=12;
    int aheight=10;
    int amode=0;
    int aborder=1;
    do
    {
        cout<<"width:"<<awidth<<" height:"<<aheight<<" mode:"<<amode<<" border:"<<aborder<<endl;
        rectNumber(awidth,aheight,amode,aborder);
        cout<<"input <width height mode border>[mode=0:out;mode=1:clockin,mode=2:anticlockin,mode=3:csborder:0(only for mode=3)]:"<<endl;
        cin>>awidth;
        cin>>aheight;
        cin>>amode;
        cin>>aborder;
    }while(awidth<=99&&aheight<=99);
}
