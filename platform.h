#ifndef PLATFORM_H
#define PLATFORM_H

// 854x480
namespace Lines
{
    const int Width = 854;
    const int Height = 480;
    const int CellSize = 52;
    const int FieldXP = 6;
    const int FieldYP = 106;
    const int FieldXL = 6;
    const int FieldYL = 6;
    const int BallImgTransX = -20;
    const int BallImgTransY = -20;
    //
    const int InfoPanelSizeXP = 360;
    const int InfoPanelSizeYP = 80;
    const int InfoPanelSizeXL = 260;
    const int InfoPanelSizeYL = 140;
    const int InfoPanelPosXP = 0;
    const int InfoPanelPosYP = 0;
    const int InfoPanelPosXL = 540;
    const int InfoPanelPosYL = 0;
    const int InfoPanelFontSize = 40;
    const int InfoPanelNextPosXP = 180;
    const int InfoPanelNextPosYP = 0;
    const int InfoPanelNextPosXL = 30;
    const int InfoPanelNextPosYL = 46;
    //
    const int ButtonQuitSize = 100;
    const int ButtonQuitIconX = 20;
    const int ButtonQuitIconY = 20;
    const int ButtonQuitXP = 360;
    const int ButtonQuitYP = 740;
    const int ButtonQuitXL = 740;
    const int ButtonQuitYL = 360;
    //
    const int ButtonNextSize = 80;
    const int ButtonNextIconX = 10;
    const int ButtonNextIconY = 10;
    const int ButtonNextXP = 160;
    const int ButtonNextYP = 750;
    const int ButtonNextXL = 500;
    const int ButtonNextYL = 240;
    //
    const int ButtonNewGameSize = 120;
    const int ButtonNewGameIconX = 25;
    const int ButtonNewGameIconY = 25;
    const int ButtonNewGameXP = 10;
    const int ButtonNewGameYP = 600;
    const int ButtonNewGameXL = 600;
    const int ButtonNewGameYL = 160;
    //
    const int ButtonHiScoresSize = 100;
    const int ButtonHiScoresIconX = 15;
    const int ButtonHiScoresIconY = 15;
    const int ButtonHiScoresXP = 340;
    const int ButtonHiScoresYP = 600;
    const int ButtonHiScoresXL = 720;
    const int ButtonHiScoresYL = 250;
    //
    const int ButtonSoundSize = 90;
    const int ButtonSoundIconX = 20;
    const int ButtonSoundIconY = 20;
    const int ButtonSoundXP = 160;
    const int ButtonSoundYP = 580;
    const int ButtonSoundXL = 540;
    const int ButtonSoundYL = 380;
    //
    const int ButtonUndoSize = 80;
    const int ButtonUndoIconX = 10;
    const int ButtonUndoIconY = 10;
    const int ButtonUndoXP = 590;
    const int ButtonUndoYP = 100;
    const int ButtonUndoXL = 500;
    const int ButtonUndoYL = 140;
    //
    const int ButtonHelpSize = 80;
    const int ButtonHelpIconX = 10;
    const int ButtonHelpIconY = 10;
    const int ButtonHelpXP = 20;
    const int ButtonHelpYP = 740;
    const int ButtonHelpXL = 740;
    const int ButtonHelpYL = 140;
    //
    const int ButtonCountSize = 90;
    const int ButtonCountIconX = 15;
    const int ButtonCountIconY = 15;
    const int ButtonCountXP = 240;
    const int ButtonCountYP = 670;
    const int ButtonCountXL = 620;
    const int ButtonCountYL = 300;
}





// 1024x600
/*namespace Lines
{
    const int Width = 1024;
    const int Height = 600;
    const int CellSize = 60;
    const int FieldXP = 6;
    const int FieldYP = 6;
    const int FieldXL = 6;
    const int FieldYL = 6;
    const int BallImgTransX = -22;
    const int BallImgTransY = -22;
}*/

// 640x360
/*namespace Lines
{
    const int Width = 640;
    const int Height = 360;
    const int CellSize = 40;
    const int FieldXP = 0;
    const int FieldYP = 80;
    const int FieldXL = 0;
    const int FieldYL = 0;
    const int BallImgTransX = -15;
    const int BallImgTransY = -13;
    //
    const int InfoPanelSizeXP = 360;
    const int InfoPanelSizeYP = 80;
    const int InfoPanelSizeXL = 254;
    const int InfoPanelSizeYL = 100;
    const int InfoPanelPosXP = 0;
    const int InfoPanelPosYP = 0;
    const int InfoPanelPosXL = 386;
    const int InfoPanelPosYL = 0;
    const int InfoPanelFontSize = 30;
    const int InfoPanelNextPosXP = 180;
    const int InfoPanelNextPosYP = 0;
    const int InfoPanelNextPosXL = 30;
    const int InfoPanelNextPosYL = 46;

    const int ButtonQuitSize = 70;
    const int ButtonQuitIconX = 5;
    const int ButtonQuitIconY = 5;
    const int ButtonQuitXP = 275;
    const int ButtonQuitYP = 560;
    const int ButtonQuitXL = 542;
    const int ButtonQuitYL = 282;
    //
    const int ButtonNextSize = 60;
    const int ButtonNextIconX = 0;
    const int ButtonNextIconY = 0;
    const int ButtonNextXP = 10;
    const int ButtonNextYP = 465;
    const int ButtonNextXL = 396;
    const int ButtonNextYL = 202;
    //
    const int ButtonNewGameSize = 80;
    const int ButtonNewGameIconX = 5;
    const int ButtonNewGameIconY = 5;
    const int ButtonNewGameXP = 160;
    const int ButtonNewGameYP = 485;
    const int ButtonNewGameXL = 476;
    const int ButtonNewGameYL = 120;
    //
    const int ButtonHiScoresSize = 90;
    const int ButtonHiScoresIconX = 10;
    const int ButtonHiScoresIconY = 10;
    const int ButtonHiScoresXP = 265;
    const int ButtonHiScoresYP = 465;
    const int ButtonHiScoresXL = 550;
    const int ButtonHiScoresYL = 190;
    //
    const int ButtonSoundSize = 60;
    const int ButtonSoundIconX = 5;
    const int ButtonSoundIconY = 5;
    const int ButtonSoundXP = 10;
    const int ButtonSoundYP = 550;
    const int ButtonSoundXL = 424;
    const int ButtonSoundYL = 290;
    //
    const int ButtonUndoSize = 65;
    const int ButtonUndoIconX = 0;
    const int ButtonUndoIconY = 0;
    const int ButtonUndoXP = 80;
    const int ButtonUndoYP = 480;
    const int ButtonUndoXL = 562;
    const int ButtonUndoYL = 112;
    //
    const int ButtonHelpSize = 60;
    const int ButtonHelpIconX = 0;
    const int ButtonHelpIconY = 0;
    const int ButtonHelpXP = 200;
    const int ButtonHelpYP = 570;
    const int ButtonHelpXL = 396;
    const int ButtonHelpYL = 114;
    //
    const int ButtonCountSize = 70;
    const int ButtonCountIconX = 10;
    const int ButtonCountIconY = 10;
    const int ButtonCountXP = 90;
    const int ButtonCountYP = 560;
    const int ButtonCountXL = 460;
    const int ButtonCountYL = 220;

}*/


// 640x480
/*namespace Lines
{
    const int Width = 640;
    const int Height = 480;
    const int CellSize = 52;
    const int FieldXP = 6;
    const int FieldYP = 106;
    const int FieldXL = 6;
    const int FieldYL = 6;
    const int BallImgTransX = -20;
    const int BallImgTransY = -20;
    //
    const int InfoPanelSizeXP = 360;
    const int InfoPanelSizeYP = 80;
    const int InfoPanelSizeXL = 260;
    const int InfoPanelSizeYL = 140;
    const int InfoPanelPosXP = 0;
    const int InfoPanelPosYP = 0;
    const int InfoPanelPosXL = 400;
    const int InfoPanelPosYL = 0;
    const int InfoPanelFontSize = 40;
    const int InfoPanelNextPosXP = 180;
    const int InfoPanelNextPosYP = 0;
    const int InfoPanelNextPosXL = 30;
    const int InfoPanelNextPosYL = 46;
    //
    const int ButtonQuitSize = 80;
    const int ButtonQuitIconX = 5;
    const int ButtonQuitIconY = 5;
    const int ButtonQuitXP = 0;
    const int ButtonQuitYP = 0;
    const int ButtonQuitXL = 560;
    const int ButtonQuitYL = 400;
    //
    const int ButtonNextSize = 70;
    const int ButtonNextIconX = 10;
    const int ButtonNextIconY = 10;
    const int ButtonNextXP = 0;
    const int ButtonNextYP = 0;
    const int ButtonNextXL = 480;
    const int ButtonNextYL = 240;
    //
    const int ButtonNewGameSize = 80;
    const int ButtonNewGameIconX = 10;
    const int ButtonNewGameIconY = 10;
    const int ButtonNewGameXP = 0;
    const int ButtonNewGameYP = 0;
    const int ButtonNewGameXL = 500;
    const int ButtonNewGameYL = 160;
    //
    const int ButtonHiScoresSize = 80;
    const int ButtonHiScoresIconX = 10;
    const int ButtonHiScoresIconY = 10;
    const int ButtonHiScoresXP = 0;
    const int ButtonHiScoresYP = 0;
    const int ButtonHiScoresXL = 500;
    const int ButtonHiScoresYL = 250;
    //
    const int ButtonSoundSize = 70;
    const int ButtonSoundIconX = 5;
    const int ButtonSoundIconY = 5;
    const int ButtonSoundXP = 0;
    const int ButtonSoundYP = 0;
    const int ButtonSoundXL = 480;
    const int ButtonSoundYL = 380;
    //
    const int ButtonUndoSize = 70;
    const int ButtonUndoIconX = 10;
    const int ButtonUndoIconY = 10;
    const int ButtonUndoXP = 0;
    const int ButtonUndoYP = 0;
    const int ButtonUndoXL = 480;
    const int ButtonUndoYL = 120;
    //
    const int ButtonHelpSize = 80;
    const int ButtonHelpIconX = 10;
    const int ButtonHelpIconY = 10;
    const int ButtonHelpXP = 0;
    const int ButtonHelpYP = 0;
    const int ButtonHelpXL = 740;
    const int ButtonHelpYL = 140;
    //
    const int ButtonCountSize = 70;
    const int ButtonCountIconX = 5;
    const int ButtonCountIconY = 5;
    const int ButtonCountXP = 0;
    const int ButtonCountYP = 0;
    const int ButtonCountXL = 480;
    const int ButtonCountYL = 300;
}*/

#endif // PLATFORM_H
