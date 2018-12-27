#ifndef DRAW_H
#define DRAW_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QLabel>

class Draw : public QWidget
{
public:
    Draw();
    enum Options {None,Pen,Rectangle,Erase,Fill};

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

    void resizeEvent(QResizeEvent *event) override;
    void undo();
    void redo();
    bool saveFile();
    void openFile();
    void newSheet();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void prepareForDraw();
    void draw(const QPointF &movePoint);
    void erase(const QPointF &movePoint);
    void fill(const QPoint &current);
    void fillSurface(int x,int y,QRgb targetCol,QRgb fillCol);


    int mPenWidth;
    int pixCurrent;
    int xMax;
    int yMax;
    int maxUndoStep = 5;
    int undoCurrent;
    bool modified;
    bool drawing;

    Options mOption;
    QVector<QPixmap*> pixmapList;
    QPainter *painter;
    QLabel *label;
    QColor mPenColor;
    QPainterPath *path;
    QPainterPath *pathE;
    QImage *img;
};

#endif // DRAW_H
