#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include "draw.h"

Draw::Draw()
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    drawing = false;
    mPenWidth = 1;
    mPenColor = Qt::black;
    xMax = 1350;
    yMax = 700;
    label = new QLabel(this);
    pixmapList.push_back(new QPixmap(xMax,yMax));
    pixCurrent = pixmapList.size() - 1;
    pixmapList[pixCurrent]->fill();
    painter = new QPainter(pixmapList[pixCurrent]);
    label->setPixmap(*pixmapList[pixCurrent]);
}

void Draw::setPenWidth(int newWidth)
{
    mPenWidth = newWidth;
}

void Draw::setPenColor(const QColor &newColor)
{
    mPenColor = newColor;
}

void Draw::setOption(const Draw::Options &option)
{
    mOption = option;
}

void Draw::setWidth(int width)
{
    xMax = width;
}

void Draw::setHeight(int height)
{
    yMax = height;
}

void Draw::setUndoCurrent(int newUndoCurrent)
{
    undoCurrent = newUndoCurrent;
}

void Draw::prepareForDraw()
{
    if(pixCurrent == maxUndoStep){
        pixmapList.push_back(new QPixmap(xMax,yMax));
        QPixmap *tmp = pixmapList.takeFirst();
        delete tmp;
        pixmapList[pixCurrent]->operator =(*pixmapList[pixCurrent-1]);
        delete painter;
        painter = new QPainter(pixmapList[pixCurrent]);
    }else{
        pixmapList.push_back(new QPixmap(xMax,yMax));
        pixCurrent += 1;
        undoCurrent = pixCurrent;
        pixmapList[pixCurrent]->operator =(*pixmapList[pixCurrent-1]);
        delete painter;
        painter = new QPainter(pixmapList[pixCurrent]);
    }

}

void Draw::resizeEvent(QResizeEvent *event)
{
    xMax = event->size().width();
    yMax = event->size().height();
    resize(xMax,yMax);
}

void Draw::undo()
{
    if(undoCurrent == 0) return;
    undoCurrent -= 1;
    label->setPixmap(*pixmapList[undoCurrent]);
}

void Draw::redo()
{

    if(undoCurrent == pixCurrent) return;
    undoCurrent+=1;
    label->setPixmap(*pixmapList[undoCurrent]);
}

bool Draw::saveFile()
{
    QString file = QFileDialog::getSaveFileName(nullptr, "Save image", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    modified = false;
    return pixmapList[pixCurrent]->save(file);
}

void Draw::openFile(){
    QString file = QFileDialog::getOpenFileName(nullptr,"Open image",QString(),"Images (*.png *.gif *.jpg *.jpeg)");
    delete painter;
    pixmapList.remove(pixCurrent);
    pixmapList.push_back(new QPixmap(file));
    painter = new QPainter(pixmapList[pixCurrent]);
    label->setPixmap(*pixmapList[pixCurrent]);
    modified = true;
}

void Draw::newSheet()
{
    painter->end();
    delete painter;
    pixmapList.erase(pixmapList.begin(),pixmapList.end());
    delete label;

    pixmapList.push_back(new QPixmap(xMax,yMax));
    pixCurrent = pixmapList.size()-1;
    undoCurrent = pixCurrent;
    pixmapList[pixCurrent]->fill();

    label = new QLabel(this);
    label->setPixmap(*pixmapList[pixCurrent]);
    label->show();
    painter = new QPainter(pixmapList[pixCurrent]);
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    if(undoCurrent != pixCurrent){
        pixmapList.erase(pixmapList.begin()+undoCurrent+1,pixmapList.end());
        pixCurrent = undoCurrent;
    }
    if (event->button() == Qt::LeftButton) {
        if(mOption == Pen){
            prepareForDraw();
            path = new QPainterPath(QPointF(event->pos().x(),event->pos().y()));
            path->moveTo(event->pos().x(),event->pos().y());
        }else if(mOption == Rectangle){

        }else if(mOption == Erase){
            prepareForDraw();
            pathE = new QPainterPath(QPointF(event->pos().x(),event->pos().y()));
            pathE->moveTo(event->pos().x(),event->pos().y());
        }else if(mOption == Fill){
            fill(event->pos());
        }
        drawing = true;
    }
}

void Draw::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing){
        if(mOption == Pen){
            draw(event->pos());
        }else if(mOption == Rectangle){

        }else if(mOption == Erase){
            erase(event->pos());
        }
    }
}

void Draw::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        if(mOption == Pen){
            delete path;
        }else if(mOption == Rectangle){

        }else if(mOption == Erase){
            delete pathE;
        }
        drawing = false;
    }
}

void Draw::draw(const QPointF &movePoint)
{
    path->lineTo(movePoint.x(),movePoint.y());
    painter->setPen(QPen(mPenColor,mPenWidth,Qt::SolidLine,Qt::RoundCap));
    painter->drawPath(*path);
    painter->setRenderHint(QPainter::Antialiasing);
    label->setPixmap(*pixmapList[pixCurrent]);
    modified=true;
}

void Draw::erase(const QPointF &movePoint)
{
    pathE->lineTo(movePoint.x(),movePoint.y());
    if(mPenWidth < 10) painter->setPen(QPen(Qt::white,10));
    else painter->setPen(QPen(Qt::white,mPenWidth));
    painter->drawPath(*pathE);
    painter->setRenderHint(QPainter::Antialiasing);
    label->setPixmap(*pixmapList[pixCurrent]);
    modified=true;
}

void Draw::fill(const QPoint &current)
{
    painter->end();
    delete painter;
    QRgb colorTarget,colorFill;
    QColor colorBuff;

    pixmapList.push_back(new QPixmap(xMax,yMax));
    pixCurrent = pixCurrent+1;
    pixmapList[pixCurrent]->operator =(*pixmapList[pixCurrent-1]);


    img = new QImage(xMax,yMax,QImage::Format_RGB32);
    *img = pixmapList[pixCurrent]->toImage();
    colorTarget = img->pixel(current.x(),current.y());
    colorFill = mPenColor.rgb();
    fillSurface(current.x(),current.y(),colorTarget,colorFill);

    pixmapList[pixCurrent]->convertFromImage(*img);
    painter = new QPainter(pixmapList[pixCurrent]);

    delete img;

    label->setPixmap(*pixmapList[pixCurrent]);
}

void Draw::fillSurface(int x, int y, QRgb targetCol, QRgb fillCol)
{
    int a,b,i;
    int lastPosition;
    QVector<QPoint*> positionsList;

    if(img->pixel(x,y) != targetCol) return;
    if(x<0 || y<0 || x > (xMax-1) || y > (yMax-1) || targetCol==fillCol) return;

    positionsList.push_back(new QPoint(x,y));

    while(!positionsList.empty())
    {
        a = positionsList[positionsList.size()-1]->x();
        b = positionsList[positionsList.size()-1]->y();

        if(a==1||b==1||a==(xMax-1)||b==(yMax-1))
        {
            for(i=0;i<xMax;i++)
            {
               img->setPixel(i,0,fillCol);
               img->setPixel(i,yMax-1,fillCol);
            }
            for(i=0;i<yMax;i++)
            {
               img->setPixel(0,i,fillCol);
               img->setPixel(xMax-1,i,fillCol);
            }
        }
        lastPosition = positionsList.size()-1;
        positionsList.remove(lastPosition);

        img->setPixel(a,b,fillCol);

        if(img->pixel(a,b-1)==targetCol)
        {
            positionsList.push_back(new QPoint(a,b-1));
        }

        if(img->pixel(a,b+1)==targetCol)
        {
            positionsList.push_back(new QPoint(a,b+1));
        }
        if(img->pixel(a+1,b)==targetCol)
        {
            positionsList.push_back(new QPoint(a+1,b));
        }
        if(img->pixel(a-1,b)==targetCol)
        {
            positionsList.push_back(new QPoint(a-1,b));
        }
    }
}

