#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class View;

class GraphicsView : public QGraphicsView
{
	 Q_OBJECT
public:
	 GraphicsView(View *v) : QGraphicsView(), view(v) { }

protected:
#ifndef QT_NO_WHEELEVENT
	 void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;
#endif

private:
	 View *view;
};

class View : public QFrame
{
	 Q_OBJECT
public:
	 explicit View(const QString &name, QWidget *parent = 0);
	 QGraphicsView *view() const;
	 void scroll(int dx, int dy);

public slots:
	 void zoomIn(int level = 1);
	 void zoomOut(int level = 1);

private slots:
	 void resetView();
	 void setResetButtonEnabled();
	 void setupMatrix();


private:
	 GraphicsView *graphicsView;
	 QLabel *label;
	 QToolButton *resetButton;
	 QSlider *zoomSlider;
};

#endif // VIEW_H
