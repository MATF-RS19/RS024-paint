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
    ~Draw() override;
    enum Options {None,Pen,Rectangle,Erase,Fill,Circle,Triangle};

    bool isModified() const { return modified; }

    int penWidth() const { return mPenWidth; }
    void setPenWidth(int newWidth);

    QColor penColor() const { return mPenColor; }
    void setPenColor(const QColor &newColor);

    Options option() const {return mOption;}
    void setOption(const Options &option);

    void setWidth(int width);
    void setHeight(int height);

    int getUndoCurrent() {return undoCurrent;}
    void setUndoCurrent(int newUndoCurrent);

    int getPixCurrent(){return pixCurrent;}

    void undo();
    void redo();
    bool saveFile();
    void openFile();
    void newSheet();
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
    void drawTmpRect(const QPointF &current);
    void drawRect(const QPointF &current);
    int mPenWidth;
    int pixCurrent;
    int xMax;
    int yMax;
    int maxUndoStep = 5;
    int undoCurrent;
    bool modified;
    bool drawing;

    Options mOption;
    QList<QPixmap> pixmapList;
    QPainter *painter;
    QColor mPenColor;
    QPainterPath *path;
    QPainterPath *pathE;
    QImage *img;
    QPointF startPoint;
};

#endif // DRAW_H
