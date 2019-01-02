#ifndef DRAW_H
#define DRAW_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QLabel>
#include <QGraphicsPixmapItem>

class Draw : public QGraphicsPixmapItem
{
public:
    Draw();
    Draw(int height, int width);
    ~Draw() override;
    enum Options {None,Pen,Rectangle,Erase,Fill,Circle,Triangle, Ellipse, Line};

    void setModified(bool value) { modified = value; }
    bool isModified() const { return modified; }

    int penWidth() const { return mPenWidth; }
    void setPenWidth(int newWidth);

    QColor penColor() const { return mPenColor; }
    void setPenColor(const QColor &newColor);

    Options option() const {return mOption;}
    void setOption(const Options &option);

    void setWidth(int width);
    int getWidth(){return xMax;}

    void setHeight(int height);
    int getHeight(){return yMax;}

    int getUndoCurrent() {return undoCurrent;}
    void setUndoCurrent(int newUndoCurrent);


    QPixmap getpixMapList(int index) const { return pixmapList[index]; }
    int getPixCurrent(){return pixCurrent;}

    QString getFile() const { return file; }


    void undo();
    void redo();
    bool saveFile();
    bool saveSameFile();
    void openFile();
    void newSheet();
    void zoomIn();
    void zoomOut();
    void resetZoom();
    QPixmap getLastPixmap() const;
protected:
    void	mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    void	mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void	mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

private:
    void prepareForDraw();
    void draw(const QPointF &movePoint);
    void erase(const QPointF &movePoint);
    void fill(const QPointF &current);
    void fillSurface(int x,int y,QRgb targetCol,QRgb fillCol);
    void drawTmp(const QPointF &current, Options shape);
    void drawRect(const QPointF &current);
    void drawCircle(const QPointF &current);
    void drawEllipse(const QPointF &current);
    void drawTriangle(const QPointF &current);
    void drawLine(const QPointF &current);

    int mPenWidth;
    int pixCurrent;
    int xMax;
    int yMax;
    int maxUndoStep = 5;
    int undoCurrent;

    double zoomStep = 0.20;

    bool modified;
    bool saved;
    bool drawing;

    QString file;
    Options mOption;
    QList<QPixmap> pixmapList;
    QPainter *painter;
    QColor mPenColor;
    QPainterPath *path;
    QPainterPath *pathE;
    QImage img;
    QPointF startPoint;
};

#endif // DRAW_H
