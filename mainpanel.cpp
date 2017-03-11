#include "mainpanel.h"

#include <QPainter>
#include <QGraphicsSceneResizeEvent>
#include <QSettings>
#include <QSound>
#include <QDebug>

#include <QMediaPlayer>

#include "platform.h"

#include "anim.h"
#include "button.h"
#include "scene.h"
#include "infopanel.h"
#include "hiscores.h"
#include "yesno.h"
#include "gameover.h"
#include "help.h"
#include "resources.h"
#include "boom.h"
#include "bubble.h"
#include "sound.h"

Lines::MainPanel::MainPanel()
    : m_newColors(3)
    , m_animator(new Lines::Animator(this))
    , m_sound(true)
    , m_volume(40)
    , m_lineCount(5)
    , m_showPreview(true)
    , m_score(0)
{
    setZValue(0);

    m_hiScores = new Lines::HiScores(this);
    m_help = new Lines::Help(this);
    m_infoPanel = new Lines::InfoPanel(this);

    loadConfig();
    m_infoPanel->setShowNext(m_showPreview);


    /////////////////
    m_quitButton = new Lines::Button(this);
    m_quitButton->resize(Lines::ButtonQuitSize, Lines::ButtonQuitSize);
    m_quitButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::Quit), QPoint(Lines::ButtonQuitIconX, Lines::ButtonQuitIconY));
    connect(m_quitButton, SIGNAL(pressed()), SLOT(onQuitButtonClicked()));
    /////////////////
    m_nextButton = new Lines::Button(this);
    m_nextButton->resize(Lines::ButtonNextSize, Lines::ButtonNextSize);
    m_nextButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::Preview), QPoint(Lines::ButtonNextIconX, Lines::ButtonNextIconY));
    connect(m_nextButton, SIGNAL(pressed()), SLOT(onPreviewButtonClicked()));
    /////////////////
    m_newGameButton = new Lines::Button(this);
    //m_newGameButton->setEnabled(false);
    m_newGameButton->resize(Lines::ButtonNewGameSize, Lines::ButtonNewGameSize);
    m_newGameButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::NewGame), QPoint(Lines::ButtonNewGameIconX, Lines::ButtonNewGameIconX));
    connect(m_newGameButton, SIGNAL(pressed()), SLOT(onNewGameButtonClicked()));
    //connect(m_newGameButton, SIGNAL(pressed()), SLOT(startNewGame()));
    /////////////////
    m_showHiScores = new Lines::Button(this);
    m_showHiScores->resize(Lines::ButtonHiScoresSize, Lines::ButtonHiScoresSize);
    m_showHiScores->setIcon(Lines::Resources::self()->icon(Lines::Resources::HiScores), QPoint(Lines::ButtonHiScoresIconX, Lines::ButtonHiScoresIconY));
    connect(m_showHiScores, SIGNAL(pressed()), SLOT(onHiScoresButtonClicked()));
    /////////////////
    m_soundButton = new Lines::Button(this);
    m_soundButton->resize(Lines::ButtonSoundSize, Lines::ButtonSoundSize);
    m_soundButton->setIcon(Lines::Resources::self()->icon((m_sound) ? Lines::Resources::SoundOn : Lines::Resources::SoundOff), QPoint(ButtonSoundIconX, ButtonSoundIconY));
    connect(m_soundButton, SIGNAL(pressed()), SLOT(onSoundButtonClicked()));
    /////////////////
    m_undoButton = new Lines::Button(this);
    m_undoButton->resize(Lines::ButtonUndoSize, Lines::ButtonUndoSize);
    m_undoButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::Undo), QPoint(Lines::ButtonUndoIconX, Lines::ButtonUndoIconY));
    connect(m_undoButton, SIGNAL(pressed()), SLOT(onUndoButtonClicked()));
    /////////////////
    m_helpButton = new Lines::Button(this);
    m_helpButton->resize(Lines::ButtonHelpSize, Lines::ButtonHelpSize);
    m_helpButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::Help), QPoint(Lines::ButtonHelpIconX, Lines::ButtonHelpIconY));
    connect(m_helpButton, SIGNAL(pressed()), SLOT(onHelpButtonClicked()));
    /////////////////
    m_countButton = new Lines::Button(this);
    m_countButton->resize(Lines::ButtonCountSize, Lines::ButtonCountSize);
    switch(m_lineCount)
    {
    case 3:
        m_countButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::Count3), QPoint(Lines::ButtonCountIconX, Lines::ButtonCountIconY));
        break;
    case 4:
        m_countButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::Count4), QPoint(Lines::ButtonCountIconX, Lines::ButtonCountIconY));
        break;
    case 5:
        m_countButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::Count5), QPoint(Lines::ButtonCountIconX, Lines::ButtonCountIconY));
        break;
    }
    connect(m_countButton, SIGNAL(pressed()), SLOT(onCountButtonClicked()));

    m_zoomedField = new QGraphicsPixmapItem(*Lines::Resources::self()->fieldZoomed(), this);
    m_zoomedField->hide();
    m_zoomedField->setOpacity(0.75);
    m_zoomedField->setZValue(50.0);

    m_fieldShadow = new QGraphicsRectItem(this);
    m_fieldShadow->setBrush(QBrush(Qt::black));
    m_fieldShadow->show();
    m_fieldShadow->setOpacity(0.8);
    m_fieldShadow->setZValue(60.0);

    m_selected = 0;
    for(int i = 0; i < Lines::CellsNumber; i++)
        for(int j = 0; j < Lines::CellsNumber; j++)
            m_fields[i][j] = 0;

    connect(m_animator, SIGNAL(moveFinished()), SLOT(onMoveFinished()));
    connect(m_animator, SIGNAL(createFinished()), SLOT(onCreateFinished()));
    connect(m_animator, SIGNAL(removeFinished()), SLOT(onRemoveFinished()));

    Sound::self()->init(m_volume, m_sound);

    if(m_gameActive)
    {
        m_gameActive = false;
        askLoadGame();
    }

    Sound::self()->musicSet(Lines::Resources::self()->sound(Lines::Resources::Music));
    updateGameState();

    Lines::Bubble *bubble;
    bubble = new Lines::Bubble(this);
    bubble->setText(tr("Start"));
    bubble->setPos(Lines::ButtonNewGameXP + 40, Lines::ButtonNewGameYP - 20);
    bubble->show();
    bubble = new Lines::Bubble(this);
    bubble->setText(tr("Help"));
    bubble->setPos(Lines::ButtonHelpXP + 40, Lines::ButtonHelpYP - 20);
    bubble->show();
}

void Lines::MainPanel::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    p->fillRect(boundingRect(), QBrush(Qt::black));
    if(m_orientation)
        p->drawPixmap(0, 0, *Lines::Resources::self()->backgroundPortrait());
    else
        p->drawPixmap(0, 0, *Lines::Resources::self()->backgroundLandscape());
    int x = m_fieldRect.x();
    int y = m_fieldRect.y();
    for(int i = 0; i < Lines::CellsNumber; i++)
        for(int j = 0; j < Lines::CellsNumber; j++)
            //if (m_access[i][j] == -1)
                p->drawPixmap(x + j * Lines::CellSize, y + i * Lines::CellSize, Lines::CellSize, Lines::CellSize, *Lines::Resources::self()->field());
            //else
            //	p->drawPixmap(x + j * m_cellSize, y + i * m_cellSize, m_cellSize, m_cellSize, *Lines::Resources::self()->fieldHighlighted());
}

void Lines::MainPanel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "gggg";
    //QGraphicsWidget::mousePressEvent(event);
    if(m_animator->isActive() || !m_gameActive)
        return;
    if (!m_fieldRect.contains(event->scenePos().toPoint()))
        return;
    //qDebug() << event->scenePos();
    //qDebug() << itemAt(event->scenePos());
    if(m_selected)
    {
        Cell to = point2cell(event->scenePos().toPoint());
        if(getBall(to) || !isReachable(to))
            m_zoomedField->hide();
        else
            showZoomedField(to);
    }
}

void Lines::MainPanel::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "release";
    //QGraphicsWidget::mouseReleaseEvent(event);
    if(m_animator->isActive() || !m_gameActive)
        return;
    if (!m_fieldRect.contains(event->scenePos().toPoint()))
        return;
    Cell to = point2cell(event->scenePos().toPoint());
    Lines::Ball *ball = getBall(to);
    if(ball)
    {
        if(m_selected)
            m_selected->deselect();
        m_selected = ball;
        m_selected->select();
        clearAccess();
        calcAccess(to);
        update();
        return;
    }
    if(m_selected)
    {
        m_zoomedField->hide();
        //qDebug() << to;
        Cell from = m_selected->cell();
        QList<Cell> path;
        bool r = findPath(from, to, path);
        if(r)
        {
            addUndoInfo();
            m_animator->startMove(m_selected, path);
            m_selected->deselect();
        }
    }
}

void Lines::MainPanel::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsWidget::mouseMoveEvent(event);
    if(m_animator->isActive() || !m_gameActive)
        return;
    if (!m_fieldRect.contains(event->scenePos().toPoint()))
        return;
    if(m_selected)
    {
        Cell to = point2cell(event->scenePos().toPoint());
        if(getBall(to) || !isReachable(to))
            m_zoomedField->hide();
        else
            showZoomedField(to);
    }
}

void Lines::MainPanel::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    int w = event->newSize().width();
    int h = event->newSize().height();
    qDebug() << "resize " << event->newSize();
    m_orientation = (h > w);
    m_fieldRect = QRect(0, 0, Lines::CellSize * Lines::CellsNumber, Lines::CellSize * Lines::CellsNumber);
    if(m_orientation)
        m_fieldRect.moveTo(FieldXP, FieldYP);
    else
        m_fieldRect.moveTo(FieldXL, FieldYL);
    //m_fieldRect.moveTop(80);
    m_fieldShadow->setRect(m_fieldRect);
    m_infoPanel->setOrientation(m_orientation);

    for(int i = 0; i < Lines::CellsNumber; i++)
        for(int j = 0; j < Lines::CellsNumber; j++)
            if(m_fields[i][j])
                updateBall(m_fields[i][j]);

    if(m_orientation)
    {
        m_newGameButton->setPos(Lines::ButtonNewGameXP, Lines::ButtonNewGameYP);
        m_helpButton->setPos(Lines::ButtonHelpXP, Lines::ButtonHelpYP);
        m_nextButton->setPos(Lines::ButtonNextXP, Lines::ButtonNextYP);
        m_countButton->setPos(Lines::ButtonCountXP, Lines::ButtonCountYP);
        m_showHiScores->setPos(Lines::ButtonHiScoresXP, Lines::ButtonHiScoresYP);
        m_soundButton->setPos(Lines::ButtonSoundXP, Lines::ButtonSoundYP);
        m_undoButton->setPos(Lines::ButtonUndoXP, Lines::ButtonUndoYP);
        m_quitButton->setPos(Lines::ButtonQuitXP, Lines::ButtonQuitYP);

        m_infoPanel->setPos(Lines::InfoPanelPosXP, Lines::InfoPanelPosYP);
    }
    else
    {
        m_newGameButton->setPos(Lines::ButtonNewGameXL, Lines::ButtonNewGameYL);
        m_helpButton->setPos(Lines::ButtonHelpXL, Lines::ButtonHelpYL);
        m_nextButton->setPos(Lines::ButtonNextXL, Lines::ButtonNextYL);
        m_countButton->setPos(Lines::ButtonCountXL, Lines::ButtonCountYL);
        m_showHiScores->setPos(Lines::ButtonHiScoresXL, Lines::ButtonHiScoresYL);
        m_soundButton->setPos(Lines::ButtonSoundXL, Lines::ButtonSoundYL);
        m_undoButton->setPos(Lines::ButtonUndoXL, Lines::ButtonUndoYL);
        m_quitButton->setPos(Lines::ButtonQuitXL, Lines::ButtonQuitYL);

        m_infoPanel->setPos(Lines::InfoPanelPosXL, Lines::InfoPanelPosYL);
    }

    updatePanels();
}

void Lines::MainPanel::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key +" << event->key();
}

void Lines::MainPanel::keyReleaseEvent(QKeyEvent *event)
{
    qDebug() << "Key -" << event->key();
}


void Lines::MainPanel::endTurn()
{
    QList<Lines::Ball *> balls;
    bool b = placeNewBalls(balls);
    if (b)
    {
        onGameOver();
        return;
    }
    m_animator->startCreate(balls);
}

void Lines::MainPanel::onMoveFinished()
{
    //clearAccess();
    //update();
    Cell to = m_animator->moveEndPoint();
    placeBall(m_selected, to.first, to.second);
    qDebug() << m_selected->pos();
    m_selected = 0;
    QList<Lines::Ball *> balls;
    findLines(balls);
    if(balls.count() > 0)
        m_animator->startRemove(balls);
    else
        endTurn();
}

void Lines::MainPanel::onCreateFinished()
{
    foreach(Lines::Ball *ball, m_animator->balls())
        ball->setFrame(6);
    createNewBalls();
    // Find lines
    QList<Lines::Ball *> balls;
    findLines(balls);
    if(balls.count() > 0)
        m_animator->startRemove(balls);
    //// MAIN STATE
}

void Lines::MainPanel::onRemoveFinished()
{
    QList<Lines::Ball *> balls = m_animator->balls();
    int b = balls.count();
    foreach(Lines::Ball *ball, balls)
    {
        //Lines::Boom *boom = new Lines::Boom(ball->color(), this);
        //boom->start(fieldPoint(ball->cell()) + QPoint(20, 20));

        Sound::self()->play(Lines::Resources::Boom);

        m_fields[ball->fieldY()][ball->fieldX()] = 0;
        delete ball;
    }
    if(m_lineCount == 5)
    {
        m_score += 2 * b * b - 20 * b + 60;
        m_infoPanel->setScore(m_score);
    }
}

void Lines::MainPanel::startNewGame()
{
    m_selected = 0;
    for(int i = 0; i < Lines::CellsNumber; i++)
        for(int j = 0; j < Lines::CellsNumber; j++)
        {
            if(m_fields[i][j])
                delete m_fields[i][j];
            m_fields[i][j] = 0;
        }
    m_freeCells = Lines::CellsNumber * Lines::CellsNumber;
    m_score = 0;
    m_infoPanel->setScore(m_score);
    m_infoPanel->setShowScore(m_lineCount == 5);
    m_gameActive = true;
    updateGameState();

    clearAccess();
    createNewBalls();
    endTurn();
}

void Lines::MainPanel::restoreGame()
{
    m_selected = 0;

    QSettings settings(OrgName, AppName);
    settings.beginGroup("CurrentGame");

    m_newColors[0] = (Lines::Ball::Color)settings.value("Next0", Lines::Ball::Red).toInt();
    m_newColors[1] = (Lines::Ball::Color)settings.value("Next1", Lines::Ball::Green).toInt();
    m_newColors[2] = (Lines::Ball::Color)settings.value("Next2", Lines::Ball::Blue).toInt();
    m_infoPanel->setNextColors(m_newColors);

    m_freeCells = Lines::CellsNumber * Lines::CellsNumber;
    for(int y = 0; y < Lines::CellsNumber; y++)
        for(int x = 0; x < Lines::CellsNumber; x++)
        {
            m_fields[y][x] = 0;
            QString key = QString("Field%1-%2").arg(x).arg(y);
            Lines::Ball::Color c = (Lines::Ball::Color)settings.value(key, Lines::Ball::None).toInt();
            if (c == Lines::Ball::None)
                continue;
            Lines::Ball *ball = new Lines::Ball(c);
            placeBall(ball, x, y);
            ball->setFrame(6);
            ball->show();
            m_freeCells--;
        }
    m_score = settings.value("Score", 0).toInt();
    m_infoPanel->setScore(m_score);
    m_infoPanel->setShowScore(m_lineCount == 5);

    m_gameActive = true;
    updateGameState();
    settings.endGroup();

    clearAccess();
    //createNewBalls();
    //endTurn();
}

void Lines::MainPanel::onGameOver()
{
    m_gameActive = false;
    m_undoStack.clear();
    updateGameState();
    bool add = m_hiScores->canAdd(m_score) && m_lineCount == 5;
    Lines::GameOver *gameOver = new Lines::GameOver(this);
    connect(gameOver, SIGNAL(closed()), SLOT(onGameOverPanelClosed()));
    gameOver->setMode(add, m_hiScores->lastName());
    gameOver->show();
    updatePanels();
}

void Lines::MainPanel::onGameOverPanelClosed()
{
    Lines::GameOver *gameOver = qobject_cast<Lines::GameOver *>(sender());
    if(!gameOver)
        return;
    bool r = gameOver->mode();
    QString name = gameOver->name();
    delete gameOver;
    if(r)
    {
        m_hiScores->addNewScore(name, m_score);
        m_hiScores->setLastName(name);
    }
    m_score = 0;
    m_infoPanel->setScore(m_score);
}

void Lines::MainPanel::onNewGameButtonClicked()
{
    if(m_gameActive)
    {
        Lines::YesNo *yesNo = new Lines::YesNo(this);
        yesNo->setText(tr("Do you want end game?"));
        yesNo->show();
        updatePanels();
        connect(yesNo, SIGNAL(closed()), SLOT(onNewGameYesNoClosed()));
    }
    else
    {
        startNewGame();
    }

    //onGameOver();
}

void Lines::MainPanel::onNewGameYesNoClosed()
{
    Lines::YesNo *yesNo = qobject_cast<Lines::YesNo *>(sender());
    if(!yesNo)
        return;
    bool r = yesNo->result();
    delete yesNo;
    if(!r)
        return;
    m_gameActive = false;
    m_undoStack.clear();
    updateGameState();
}

void Lines::MainPanel::onUndoButtonClicked()
{
    if(m_animator->isActive())
        return;
    clearSelection();
    restoreUndoInfo();
}

void Lines::MainPanel::onPreviewButtonClicked()
{
    m_showPreview = !m_showPreview;
    m_infoPanel->setShowNext(m_showPreview);
}

void Lines::MainPanel::onSoundButtonClicked()
{
    m_sound = !m_sound;
    m_soundButton->setIcon(Lines::Resources::self()->icon((m_sound) ? Lines::Resources::SoundOn : Lines::Resources::SoundOff), QPoint(ButtonSoundIconX, ButtonSoundIconY));
    if(m_sound)
        Sound::self()->soundOn();
    else
        Sound::self()->soundOff();
}

void Lines::MainPanel::onHiScoresButtonClicked()
{
    m_hiScores->show();
    updatePanels();
}

void Lines::MainPanel::onHelpButtonClicked()
{
    m_help->show();
    updatePanels();
}

void Lines::MainPanel::onCountButtonClicked()
{
    if(m_gameActive)
        return;
    m_lineCount++;
    if(m_lineCount > 5)
        m_lineCount = 4;

    switch(m_lineCount)
    {
    case 3:
        m_countButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::Count3), QPoint(Lines::ButtonCountIconX, Lines::ButtonCountIconY));
        break;
    case 4:
        m_countButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::Count4), QPoint(Lines::ButtonCountIconX, Lines::ButtonCountIconY));
        break;
    case 5:
        m_countButton->setIcon(Lines::Resources::self()->icon(Lines::Resources::Count5), QPoint(Lines::ButtonCountIconX, Lines::ButtonCountIconY));
        break;
    }
    m_infoPanel->setShowScore(m_lineCount == 5);
}

void Lines::MainPanel::onQuitButtonClicked()
{
    Lines::YesNo *yesNo = new Lines::YesNo(this);
    yesNo->setText(tr("Are you sure to quit?"));
    yesNo->show();
    updatePanels();
    connect(yesNo, SIGNAL(closed()), SLOT(onQuitYesNoClosed()));
}

void Lines::MainPanel::onQuitYesNoClosed()
{
    Lines::YesNo *yesNo = qobject_cast<Lines::YesNo *>(sender());
    if(!yesNo)
        return;
    bool r = yesNo->result();
    delete yesNo;
    if(!r)
        return;
    saveConfig();
    emit closed();
}

void Lines::MainPanel::onAskLoadGamseClosed()
{
    Lines::YesNo *yesNo = qobject_cast<Lines::YesNo *>(sender());
    if(!yesNo)
        return;
    bool r = yesNo->result();
    delete yesNo;
    if(!r)
        return;
    restoreGame();
}

QPoint Lines::MainPanel::fieldPoint(Cell c) const
{
    return fieldPoint(c.first, c.second);
}

void Lines::MainPanel::createNewBalls()
{
    for (int i = 0; i < 3; i++)
        m_newColors[i] = Lines::Ball::randomColor();
    m_infoPanel->setNextColors(m_newColors);
}

bool Lines::MainPanel::placeNewBalls(QList<Lines::Ball *> &balls)
{
    QList<Cell> freecells;
    for(int y = 0; y < Lines::CellsNumber; y++)
        for(int x = 0; x < Lines::CellsNumber; x++)
            if(!m_fields[y][x])
                freecells << Cell(x, y);
    for(int i = 0; i < 3; i++)
        if(freecells.count() > 0)
        {
            int r = rand() % freecells.count();
            Cell c = freecells.takeAt(r);
            Lines::Ball *ball = new Lines::Ball(m_newColors[i]);
            placeBall(ball, c.first, c.second);
            balls << ball;
        }
    if(freecells.count() == 0)
    {
        qDebug() << "game over";
        return true;
    }
    return false;
}

QPoint Lines::MainPanel::fieldPoint(int x, int y) const
{
    QPoint p(Lines::CellSize * x, Lines::CellSize * y);
    p += m_fieldRect.topLeft();
    return p;
}

Cell Lines::MainPanel::point2cell(const QPoint &p) const
{
    Cell c(-1, -1);
    if(!m_fieldRect.contains(p))
        return c;
    QPoint pp = p - m_fieldRect.topLeft();
    c.first = pp.x() / Lines::CellSize;
    c.second = pp.y() / Lines::CellSize;
    return c;
}

void Lines::MainPanel::placeBall(Lines::Ball *ball, int x, int y)
{
    if(m_fields[y][x])
        return;
    if(ball->fieldX() != -1 && ball->fieldY() != -1)
        m_fields[ball->fieldY()][ball->fieldX()] = 0;
    ball->setField(x, y);
    m_fields[y][x] = ball;
    ball->setParentItem(this);
    //if(!ball->scene())
    //	addItem(ball);
    updateBall(ball);
}

void Lines::MainPanel::updateBall(Lines::Ball *ball)
{
    ball->setPos(fieldPoint(ball->fieldX(), ball->fieldY()));
}

Lines::Ball *Lines::MainPanel::getBall(const Cell &cell) const
{
    if(cell.first == -1 || cell.second == -1)
        return 0;
    return m_fields[cell.second][cell.first];
}

bool Lines::MainPanel::isReachable(const Cell &cell) const
{
    if(cell.first == -1 || cell.second == -1)
        return false;
    return m_access[cell.second][cell.first] != -1;
}

void Lines::MainPanel::showZoomedField(const Cell &cell)
{
    QPoint pc = fieldPoint(cell);
    m_zoomedField->setPos(pc - QPoint(20, 20));
    m_zoomedField->show();
}

void Lines::MainPanel::clearSelection()
{
    if(!m_selected)
        return;
    m_selected->deselect();
    m_selected = 0;
}

void Lines::MainPanel::updateGameState()
{
    if(m_gameActive)
    {
        m_fieldShadow->hide();
        m_countButton->setEnabled(false);
        m_undoButton->setEnabled(true);
        Sound::self()->musicStop();
    }
    else
    {
        m_fieldShadow->show();
        m_countButton->setEnabled(true);
        m_undoButton->setEnabled(false);
        Sound::self()->musicPlay();
    }
}

void Lines::MainPanel::updatePanels()
{
    foreach(Lines::Panel *panel, Lines::Panel::visiblePanels())
    {
        int ww = boundingRect().width() - panel->boundingRect().width();
        int hh = boundingRect().height() - panel->boundingRect().height();
        panel->setPos(ww / 2, hh /2);
    }
}

void Lines::MainPanel::addUndoInfo()
{
    UndoInfo info;
    info.score = m_score;
    foreach(Lines::Ball::Color c, m_newColors)
        info.nextColors << c;
    for(int y = 0; y < Lines::CellsNumber; y++)
        for(int x = 0; x < Lines::CellsNumber; x++)
            if(m_fields[y][x])
                info.fieldsColors[y][x] = m_fields[y][x]->color();
            else
                info.fieldsColors[y][x] = Lines::Ball::None;
    m_undoStack.push(info);
    qDebug() << "undo count " << m_undoStack.count();
}

void Lines::MainPanel::restoreUndoInfo()
{
    if(m_undoStack.isEmpty())
        return;
    UndoInfo info = m_undoStack.pop();
    m_score = info.score;
    m_infoPanel->setScore(m_score);
    for(int i = 0; i < 3; i++)
        m_newColors[i] = info.nextColors[i];
    m_infoPanel->setNextColors(m_newColors);
    for(int y = 0; y < Lines::CellsNumber; y++)
        for(int x = 0; x < Lines::CellsNumber; x++)
            if(info.fieldsColors[y][x] == Lines::Ball::None)
            {
                if(m_fields[y][x])
                {
                    qDebug() << x <<  y;
                    // remove ball
                    delete m_fields[y][x];
                    m_fields[y][x] = 0;
                }
            }
            else
            {
                if(m_fields[y][x] && m_fields[y][x]->color() != info.fieldsColors[y][x])
                {
                    m_fields[y][x]->setColor(info.fieldsColors[y][x]);
                }
                else if(!m_fields[y][x])
                {
                    Lines::Ball *ball = new Lines::Ball(info.fieldsColors[y][x]);
                    placeBall(ball, x, y);
                    ball->show();
                }
            }
}

void Lines::MainPanel::saveConfig()
{
    QSettings settings(OrgName, AppName);
    settings.beginGroup("Config");
    settings.setValue("Sound", m_sound);
    settings.setValue("LineCount", m_lineCount);
    settings.setValue("ShowPreview", m_showPreview);
    settings.setValue("GameActive", m_gameActive);
    settings.endGroup();

    m_hiScores->saveConfig(settings);

    if(m_gameActive)
    {
        settings.beginGroup("CurrentGame");
        settings.setValue("Score", m_score);
        settings.setValue("Next0", m_newColors[0]);
        settings.setValue("Next1", m_newColors[1]);
        settings.setValue("Next2", m_newColors[2]);
        for(int y = 0; y < Lines::CellsNumber; y++)
            for(int x = 0; x < Lines::CellsNumber; x++)
            {
                QString key = QString("Field%1-%2").arg(x).arg(y);
                Lines::Ball::Color c = Lines::Ball::None;
                if(m_fields[y][x])
                    c = m_fields[y][x]->color();
                settings.setValue(key, c);
            }
        settings.endGroup();
    }
}

void Lines::MainPanel::loadConfig()
{
    QSettings settings(OrgName, AppName);
    settings.beginGroup("Config");
    m_sound = settings.value("Sound", m_sound).toBool();
    m_volume = settings.value("Volume", m_volume).toInt();
    m_lineCount = settings.value("LineCount", m_lineCount).toInt();
    m_showPreview = settings.value("ShowPreview", m_showPreview).toBool();
    m_gameActive = settings.value("GameActive", false).toBool();
    settings.endGroup();

    m_hiScores->loadConfig(settings);
}

void Lines::MainPanel::loadCurrentGame()
{
    QSettings settings(OrgName, AppName);
    settings.beginGroup("CurrentGame");
    m_sound = settings.value("Sound", m_sound).toBool();
    m_lineCount = settings.value("LineCount", m_lineCount).toInt();
    m_showPreview = settings.value("ShowPreview", m_showPreview).toBool();
    settings.endGroup();
}

void Lines::MainPanel::askLoadGame()
{
    //m_gameActive = false;
    Lines::YesNo *yesNo = new Lines::YesNo(this);
    yesNo->setText(tr("Do you want load game?"));
    yesNo->show();
    updatePanels();
    connect(yesNo, SIGNAL(closed()), SLOT(onAskLoadGamseClosed()));
}

void Lines::MainPanel::findLines(QList<Lines::Ball *> &balls)
{
    QSet<Cell> cellsForRemove;
    int len = m_lineCount;
    for(int y = 0; y < Lines::CellsNumber - len + 1; y++)
        for(int x = 0; x < Lines::CellsNumber; x++)
        {
            if(!m_fields[y][x])
                continue;
            bool f = true;
            Lines::Ball::Color c = m_fields[y][x]->color();
            for(int i = 1; i < len; i++)
                if(!m_fields[y + i][x] || m_fields[y + i][x] && m_fields[y + i][x]->color() != c)
                {
                    f = false;
                    break;
                }
            if(f)
                for(int i = 0; i < len; i++)
                    cellsForRemove << Cell(x, y + i);
            //qDebug() << "line! " << x << "  " << y;
        }
    for(int y = 0; y < Lines::CellsNumber; y++)
        for(int x = 0; x < Lines::CellsNumber - len + 1; x++)
        {
            if(!m_fields[y][x])
                continue;
            bool f = true;
            Lines::Ball::Color c = m_fields[y][x]->color();
            for(int i = 1; i < len; i++)
                if(!m_fields[y][x + i] || m_fields[y][x + i] && m_fields[y][x + i]->color() != c)
                {
                    f = false;
                    break;
                }
            if(f)
                for(int i = 0; i < len; i++)
                    cellsForRemove << Cell(x + i, y);
            //qDebug() << "line! " << x << "  " << y;
        }
    for(int y = 0; y < Lines::CellsNumber - len + 1; y++)
        for(int x = 0; x < Lines::CellsNumber - len + 1; x++)
        {
            if(!m_fields[y][x])
                continue;
            bool f = true;
            Lines::Ball::Color c = m_fields[y][x]->color();
            for(int i = 1; i < len; i++)
                if(!m_fields[y + i][x + i] || m_fields[y + i][x + i] && m_fields[y + i][x + i]->color() != c)
                {
                    f = false;
                    break;
                }
            if(f)
                for(int i = 0; i < len; i++)
                    cellsForRemove << Cell(x + i, y + i);
            //qDebug() << "line! " << x << "  " << y;
        }
    for(int y = 0; y < Lines::CellsNumber - len + 1; y++)
        for(int x = len - 1; x < Lines::CellsNumber; x++)
        {
            if(!m_fields[y][x])
                continue;
            bool f = true;
            Lines::Ball::Color c = m_fields[y][x]->color();
            for(int i = 1; i < len; i++)
                if(!m_fields[y + i][x - i] || m_fields[y + i][x - i] && m_fields[y + i][x - i]->color() != c)
                {
                    f = false;
                    break;
                }
            if(f)
                for(int i = 0; i < len; i++)
                    cellsForRemove << Cell(x - i, y + i);
            //qDebug() << "line! " << x << "  " << y;
        }

    foreach(const Cell &c, cellsForRemove)
    {
        Lines::Ball *ball = m_fields[c.second][c.first];
        balls << ball;
    }
}

bool Lines::MainPanel::findPath(const Cell &from, const Cell &to, QList<Cell> &path)
{
    path.clear();
    if(m_access[to.second][to.first] == -1)
        return false;
    Cell c = to;
    while(c != from)
    {
        path.push_front(c);
        if(!m_accesspr.contains(c))
        {
            qDebug() << "internal error";
            break;
        }
        c = m_accesspr[c];
    }
    path.push_front(c);
    return true;
}

void Lines::MainPanel::clearAccess()
{
    for(int y = 0; y < Lines::CellsNumber; y++)
        for(int x = 0; x < Lines::CellsNumber; x++)
            m_access[y][x] = -1;
    m_accesspr.clear();
}

void Lines::MainPanel::calcAccess(const Cell &from)
{
    QList<Cell> queue;
    queue << from;
    m_access[from.second][from.first] = 0;

    while(true)
    {
        if(queue.isEmpty())
        {
            break;
        }
        Cell c = queue.takeFirst();
        if(c.first > 0 && m_access[c.second][c.first - 1] == -1 && !m_fields[c.second][c.first - 1])
        {
            m_access[c.second][c.first - 1] = m_access[c.second][c.first] + 1;
            queue << Cell(c.first - 1, c.second);
            m_accesspr[Cell(c.first - 1, c.second)] = c;
        }
        if(c.first < Lines::CellsNumber - 1 && m_access[c.second][c.first + 1] == -1 && !m_fields[c.second][c.first + 1])
        {
            m_access[c.second][c.first + 1] = m_access[c.second][c.first] + 1;
            queue << Cell(c.first + 1, c.second);
            m_accesspr[Cell(c.first + 1, c.second)] = c;
        }
        if(c.second > 0 && m_access[c.second - 1][c.first] == -1 && !m_fields[c.second - 1][c.first])
        {
            m_access[c.second - 1][c.first] = m_access[c.second][c.first] + 1;
            queue << Cell(c.first, c.second - 1);
            m_accesspr[Cell(c.first, c.second - 1)] = c;
        }
        if(c.second < Lines::CellsNumber - 1 && m_access[c.second + 1][c.first] == -1 && !m_fields[c.second + 1][c.first])
        {
            m_access[c.second + 1][c.first] = m_access[c.second][c.first] + 1;
            queue << Cell(c.first, c.second + 1);
            m_accesspr[Cell(c.first, c.second + 1)] = c;
        }
    }
}
