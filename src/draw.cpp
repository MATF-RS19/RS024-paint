#include <QtWidgets>
#include "draw.h"
#include "mainwindow.h"
Draw::Draw(int height,int width)
    :xMax(width),yMax(height)
{
    modified = false;
    drawing = false;
    mPenWidth = 1;
    mPenColor = Qt::black;
    pixmapList.push_back(QPixmap(xMax,yMax));
    pixCurrent = 0;
    undoCurrent = 0;
    pixmapList[pixCurrent].fill();
    painter = new QPainter(&pixmapList[pixCurrent]);
    setPixmap(pixmapList[pixCurrent]);
    saved = false;
}

Draw::~Draw(){
    delete painter;
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
    if(pixCurrent == maxUndoStep) {
        pixmapList.push_back(QPixmap(xMax, yMax));
        pixmapList.removeFirst();
        pixmapList[pixCurrent] =(pixmapList[pixCurrent-1]);
        delete painter;
        painter = new QPainter(&pixmapList[pixCurrent]);
    } else {
        pixmapList.push_back(QPixmap(xMax, yMax));
        pixCurrent += 1;
        undoCurrent = pixCurrent;
        pixmapList[pixCurrent] = (pixmapList[pixCurrent-1]);
        delete painter;
        painter = new QPainter(&pixmapList[pixCurrent]);
    }

}

void Draw::undo()
{
    if(undoCurrent == 0) {
        return;
    }
    undoCurrent -= 1;
    setPixmap(pixmapList[undoCurrent]);
    delete painter;
    painter = new QPainter(&pixmapList[undoCurrent]);
}

void Draw::redo()
{
    if(undoCurrent == pixCurrent) {
        return;
    }
    undoCurrent += 1;
    setPixmap(pixmapList[undoCurrent]);
    delete painter;
    painter = new QPainter(&pixmapList[undoCurrent]);
}

bool Draw::saveFile()
{
    saved = true;
    file = QFileDialog::getSaveFileName(nullptr, "Save image", QString(),
                                        "Images (*.png *.gif *.jpg *.jpeg)");
    modified = false;
    return pixmapList[pixCurrent].save(file);
}

bool Draw::saveSameFile()
{
    if(!saved){
        return saveFile();
    }
    modified = false;
    return pixmapList[pixCurrent].save(file);
}

void Draw::openFile() {
    file = QFileDialog::getOpenFileName(nullptr, "Open image", QString(),
                                        "Images (*.png *.gif *.jpg *.jpeg)");
    if(!file.isEmpty() && !file.isNull()) {
        delete painter;
        pixmapList.removeLast();
        pixmapList.push_back(QPixmap(file));
        painter = new QPainter(&pixmapList[pixCurrent]);
        setPixmap(pixmapList[pixCurrent]);
    }
}

void Draw::newSheet()
{
    painter->end();
    delete painter;
    pixmapList.clear();
    pixmapList.push_back(QPixmap(xMax, yMax));
    pixCurrent = 0;
    undoCurrent = pixCurrent;
    pixmapList[pixCurrent].fill();
    setPixmap(pixmapList[pixCurrent]);
    painter = new QPainter(&pixmapList[pixCurrent]);
}

void Draw::zoomIn()
{
    double factor = scale();
    setScale(factor + zoomStep);
}

void Draw::zoomOut()
{
    double factor = scale();
    setScale(factor - zoomStep);
}

void Draw::resetZoom()
{
    setScale(1);
}

void Draw::appendPixmapList(QPixmap pixmap)
{
    if(pixCurrent == maxUndoStep) {
        pixmapList.push_back(pixmap);
        pixmapList.removeFirst();
        delete painter;
        painter = new QPainter(&pixmapList[pixCurrent]);
    } else {
        pixmapList.push_back(pixmap);
        pixCurrent += 1;
        undoCurrent = pixCurrent;
        delete painter;
        painter = new QPainter(&pixmapList[pixCurrent]);
    }
}

QPixmap Draw::getLastPixmap() const
{
    return pixmapList[pixCurrent];
}

void Draw::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if(undoCurrent != pixCurrent) {
        pixmapList.erase(pixmapList.begin()+undoCurrent+1, pixmapList.end());
        pixCurrent = undoCurrent;
    }
    if (event->button() == Qt::LeftButton) {
        if(mOption == Pen) {
            prepareForDraw();
            path = new QPainterPath(QPointF(event->pos().x(), event->pos().y()));
            path->moveTo(event->pos().x(), event->pos().y());
        } else if(mOption == Erase) {
            prepareForDraw();
            pathE = new QPainterPath(QPointF(event->pos().x(), event->pos().y()));
            pathE->moveTo(event->pos().x(), event->pos().y());
        } else if(mOption == Fill) {
            fill(event->pos());
        } else { // Rect, Circle, Triangle, Ellipse, Line
            startPoint = event->pos();
        }
        drawing = true;
    }
}

void Draw::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        if(mOption == Pen) {
            draw(event->pos());
        } else if(mOption == Rectangle) {
            drawTmp(event->pos(), Rectangle);
        } else if(mOption == Ellipse) {
            drawTmp(event->pos(), Ellipse);
        } else if(mOption == Triangle) {
            drawTmp(event->pos(), Triangle);
        } else if(mOption == Erase) {
            erase(event->pos());
        } else if(mOption == Circle){
            drawTmp(event->pos(), Circle);
        }else if(mOption == Line){
            drawTmp(event->pos(), Line);
        }
    }
}

void Draw::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        if(mOption == Pen) {
            delete path;
        } else if(mOption == Rectangle) {
            drawRect(event->pos());
        } else if(mOption == Circle) {
            drawCircle(event->pos());
        } else if(mOption == Triangle) {
            drawTriangle(event->pos());
        } else if(mOption == Erase) {
            delete pathE;
        } else if(mOption == Ellipse){
            drawEllipse(event->pos());
        } else if(mOption == Line){
            drawLine(event->pos());
        }
        drawing = false;
    }
}

void Draw::draw(const QPointF &movePoint)
{
    path->lineTo(movePoint.x(), movePoint.y());
    painter->setPen(QPen(mPenColor, mPenWidth, Qt::SolidLine, Qt::RoundCap));
    painter->drawPath(*path);
    painter->setRenderHint(QPainter::Antialiasing);
    setPixmap(pixmapList[pixCurrent]);
    modified = true;
}

void Draw::erase(const QPointF &movePoint)
{
    pathE->lineTo(movePoint.x(), movePoint.y());
    if(mPenWidth < 10) {
        painter->setPen(QPen(Qt::white, 10));
    } else {
        painter->setPen(QPen(Qt::white, mPenWidth));
    }
    painter->drawPath(*pathE);
    painter->setRenderHint(QPainter::Antialiasing);
    setPixmap(pixmapList[pixCurrent]);
    modified = true;
}

void Draw::fill(const QPointF &current)
{
    painter->end();
    delete painter;
    QRgb colorTarget, colorFill;

    if(pixCurrent == maxUndoStep) {
        pixmapList.push_back(QPixmap(xMax, yMax));
        pixmapList.removeFirst();
        pixmapList[pixCurrent] =(pixmapList[pixCurrent-1]);
    } else {
        pixmapList.push_back(QPixmap(xMax, yMax));
        pixCurrent += 1;
        undoCurrent = pixCurrent;
        pixmapList[pixCurrent] =(pixmapList[pixCurrent-1]);
    }


    img = QImage(xMax, yMax, QImage::Format_RGB32);
    img = pixmapList[pixCurrent].toImage();
    colorTarget = img.pixel(static_cast<int>(current.x()), static_cast<int>(current.y()));
    colorFill = mPenColor.rgb();
    fillSurface(static_cast<int>(current.x()), static_cast<int>(current.y()), colorTarget, colorFill);

    pixmapList[pixCurrent].convertFromImage(img);
    painter = new QPainter(&pixmapList[pixCurrent]);

    setPixmap(pixmapList[pixCurrent]);
    modified = true;
}

void Draw::fillSurface(int x, int y, QRgb targetCol, QRgb fillCol)
{
    int a,b,i;
    QVector<QPoint> positionsList;

    if(img.pixel(x,y) != targetCol) return;
    if(x<0 || y<0 || x > (xMax-1) || y > (yMax-1) || targetCol == fillCol) return;

    positionsList.push_back(QPoint(x,y));

    while(!positionsList.empty())
    {
        a = positionsList[positionsList.size()-1].x();
        b = positionsList[positionsList.size()-1].y();

        if(a==1 || b==1 || a==(xMax-1) || b==(yMax-1))
        {
            for(i=0; i<xMax; i++)
            {
                img.setPixel(i, 0, fillCol);
                img.setPixel(i, yMax-1, fillCol);
            }
            for(i=0; i<yMax; i++)
            {
                img.setPixel(0, i, fillCol);
                img.setPixel(xMax-1, i, fillCol);
            }
        }

        img.setPixel(a, b, fillCol);
        positionsList.remove(positionsList.size()-1);
        if(img.pixel(a, b-1) == targetCol)
        {
            positionsList.push_back(QPoint(a, b-1));
        }

        if(img.pixel(a, b+1) == targetCol)
        {
            positionsList.push_back(QPoint(a, b+1));
        }
        if(img.pixel(a+1, b) == targetCol)
        {
            positionsList.push_back(QPoint(a+1, b));
        }
        if(img.pixel(a-1, b) == targetCol)
        {
            positionsList.push_back(QPoint(a-1, b));
        }
    }
    modified = true;
}


void Draw::drawTmp(const QPointF &current, Options shape){
    prepareForDraw();
    painter->setPen(QPen(mPenColor, mPenWidth));
    if(shape == Rectangle) {
        painter->drawRect(QRectF(startPoint, current));
    }
    else if(shape == Ellipse) {
        painter->drawEllipse(QRectF(startPoint, current));
    }
    else if(shape == Triangle) {
        QPointF firstPoint(startPoint.x(), current.y());
        qreal Cx = (startPoint.x()+current.x())/2;
        qreal Cy = startPoint.y();
        QPointF thirdPoint(Cx, Cy);
        QPointF points[3] = {firstPoint, current, thirdPoint};
        painter->drawConvexPolygon(points, 3);
    }
    else if(shape == Circle) {
        QPointF center((startPoint.x()+current.x())/2, (startPoint.y()+current.y())/2);
        qreal radius = (current.x()-startPoint.x())/2;
        painter->drawEllipse(center, radius, radius);
    }
    else if(shape == Line) {
        painter->drawLine(startPoint, current);
    }
    setPixmap(pixmapList[pixCurrent]);
    delete painter;
    pixmapList.removeLast();
    pixCurrent = pixmapList.size()-1;
    painter = new QPainter(&pixmapList[pixCurrent]);
    modified = true;
}

void Draw::drawRect(const QPointF &current){
    prepareForDraw();
    painter->setPen(QPen(mPenColor, mPenWidth));
    painter->drawRect(QRectF(startPoint, current));
    setPixmap(pixmapList[pixCurrent]);
}

void Draw::drawCircle(const QPointF &current)
{
    prepareForDraw();
    painter->setPen(QPen(mPenColor, mPenWidth));
    QPointF center((startPoint.x()+current.x())/2, (startPoint.y()+current.y())/2);
    qreal radius = (current.x()-startPoint.x())/2;
    painter->drawEllipse(center, radius, radius);
    setPixmap(pixmapList[pixCurrent]);
}

void Draw::drawEllipse(const QPointF &current){
    prepareForDraw();
    painter->setPen(QPen(mPenColor, mPenWidth));
    painter->drawEllipse(QRectF(startPoint,current));
    setPixmap(pixmapList[pixCurrent]);
}

void Draw::drawTriangle(const QPointF &current)
{
    prepareForDraw();
    QPointF firstPoint(startPoint.x(), current.y());
    qreal Cx = (startPoint.x()+current.x())/2;
    qreal Cy = startPoint.y();
    QPointF thirdPoint(Cx, Cy);
    QPointF points[3] = {firstPoint, current, thirdPoint};
    painter->setPen(QPen(mPenColor, mPenWidth));
    painter->drawConvexPolygon(points, 3);
    setPixmap(pixmapList[pixCurrent]);
}

void Draw::drawLine(const QPointF &current)
{
    prepareForDraw();
    painter->setPen(QPen(mPenColor, mPenWidth));
    painter->drawLine(startPoint, current);
    setPixmap(pixmapList[pixCurrent]);
}
