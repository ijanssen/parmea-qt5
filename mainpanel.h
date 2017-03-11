#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QGraphicsWidget>
#include <QStack>
#include "globals.h"
#include "ball.h"

namespace Lines
{
class Button;
class Animator;
class InfoPanel;
class HiScores;
class Help;

class MainPanel : public QGraphicsWidget
{
    Q_OBJECT
public:
    MainPanel();

    //virtual QRectF boundingRect() const;
    virtual void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

signals:
    void closed();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void resizeEvent(QGraphicsSceneResizeEvent *event);
    void keyPressEvent(QKeyEvent *event );
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void endTurn();
    void onMoveFinished();
    void onCreateFinished();
    void onRemoveFinished();
    void startNewGame();
    void restoreGame();
    void onGameOver();
    void onGameOverPanelClosed();

    // buttons handlers
    void onNewGameButtonClicked();
    void onNewGameYesNoClosed();
    void onUndoButtonClicked();
    void onPreviewButtonClicked();
    void onSoundButtonClicked();
    void onHiScoresButtonClicked();
    void onHelpButtonClicked();
    void onCountButtonClicked();
    void onQuitButtonClicked();
    void onQuitYesNoClosed();
    void onAskLoadGamseClosed();

private:
    struct UndoInfo
    {
        int score;
        QList<Lines::Ball::Color> nextColors;
        Lines::Ball::Color fieldsColors[Lines::CellsNumber][Lines::CellsNumber];
    };
    friend class Lines::Animator;
    QPoint fieldPoint(Cell c) const;
    void createNewBalls();
    bool placeNewBalls(QList<Lines::Ball *> &balls);
    QPoint fieldPoint(int x, int y) const;
    Cell point2cell(const QPoint &p) const;
    void placeBall(Lines::Ball *ball, int x, int y);
    void updateBall(Lines::Ball *ball);
    Lines::Ball *getBall(const Cell &cell) const;
    bool isReachable(const Cell &cell) const;
    void showZoomedField(const Cell &cell);
    void clearSelection();

    void updateGameState();
    void updatePanels();

    void addUndoInfo();
    void restoreUndoInfo();

    void saveConfig();
    void loadConfig();
    void loadCurrentGame();

    void askLoadGame();

    void findLines(QList<Lines::Ball *> &balls);
    bool findPath(const Cell &from, const Cell &to, QList<Cell> &path);
    void clearAccess();
    void calcAccess(const Cell &from);

private:
    Lines::Animator *m_animator;
    bool m_gameActive;
    bool m_sound;
    int m_volume;
    int m_lineCount;
    bool m_showPreview;

    bool m_orientation;
    QRect m_fieldRect;
    Lines::Ball *m_fields[Lines::CellsNumber][Lines::CellsNumber];
    int m_access[Lines::CellsNumber][Lines::CellsNumber];
    QMap<Cell, Cell> m_accesspr;
    Lines::Ball *m_selected;
    QVector<Lines::Ball::Color> m_newColors;
    int m_freeCells;
    int m_score;
    QStack<UndoInfo> m_undoStack;

    Lines::InfoPanel *m_infoPanel;
    Lines::Button *m_undoButton;
    Lines::Button *m_countButton;
    Lines::Button *m_quitButton;
    Lines::Button *m_nextButton;
    Lines::Button *m_newGameButton;
    Lines::Button *m_showHiScores;
    Lines::Button *m_soundButton;
    Lines::Button *m_helpButton;

    QGraphicsPixmapItem *m_zoomedField;
    QGraphicsRectItem *m_fieldShadow;
    Lines::HiScores *m_hiScores;
    Lines::Help *m_help;
};

};

#endif // MAINPAINEL_H
