#pragma once

const double SCREEN_WIDTH = 800;
const double HALF_SCREEN_WIDTH = 400;
const double SCREEN_HEIGHT = 600;
const double HALF_SCREEN_HEIGHT = 300;
const std::string WINDOW_TITLE = "Food Tornado";

const double leftBorder = 75;
const double rightBorder = 75;
const double topBorder = 75;
const double bottomBorder = 75;


const SDL_Rect grassBackground_rect = {0, 80, 96, 32};
const double grassBackgroundHeight = 32;
const double grassBackgroundRatio = 4.25;

const SDL_Rect tallTree_rect = {1, 0, 14, 29};
const double tallTreeHeight = 29;
const double tallTreeWidth = 14;
const double tallTreeRatio = 2.75;

const SDL_Rect boulder_rect = {128, 18, 16, 12};
const double boulderHeight = 12;
const double boulderWidth = 16;
const double boulderRatio = 4;

const double alignTree_boulder = (boulderWidth * boulderRatio / 2.0) - (tallTreeWidth * tallTreeRatio / 2.0);

const double dropAreaWidth = 300;
const double dropAreaHeight = SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio;


const SDL_Rect pinkBud_rect = {99, 54, 9, 6};
const SDL_Rect yellowBud_rect = {99, 39, 9, 6};
const double budWidth = 9;
const double budHeight = 6;
const double budRatio = 4.25;

const SDL_Rect dirtBackground_rect = {0, 0, 48, 32};
const double dirtBackgroundHeight = 32;
const double dirtBackgroundRatio = 7.25; //dropAreaWidth / 48

const SDL_Rect dirtBackgroundBlend_rect = {26, 58, 28, 7};
const double dirtBackgroundBlendHeight = 7;
const double dirtBackgroundBlendRatio = 12.25;

const SDL_Rect grass_rect = {84, 23, 8, 5};
const double grassWidth = 8;
const double grassHeight = 5;
const double grassRatio = 5;





const double foodRatio = 3;
const double MAX_FOOD_WIDTH = 10;
const double MAX_FOOD_HEIGHT = 11;

const double leftDropBorder = leftBorder + boulderWidth * boulderRatio; //139
const double rightDropBorder = leftBorder + boulderWidth * boulderRatio + dropAreaWidth; //439
const double topDropBorder = topBorder + (dirtBackgroundBlendHeight / 2) * dirtBackgroundRatio;
const double bottomDropBorder = SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio; //477











const SDL_Rect menuButtons = {0, 0, 144, 72};
const SDL_Rect menuButtonsHover = {0, 72, 144, 72};



const int MAX_SPRITES = 30;

const SDL_Rect bearRect1 = {1, 210, 37, 25};
const SDL_Rect bearRect2 = {49, 210, 42, 25};
const SDL_Rect bearRect3 = {98, 210, 37, 25};

const std::string bearFilePath = {"bear.png"};

const double bearRatio = 5;



const SDL_Rect basket_rect = {16, 82, 16, 14};
const double basketWidth = 16;
const double basketHeight = 14;
const double basketRatio = 5;




const SDL_Rect cowRect1 = {1, 0, 31, 31};
const SDL_Rect cowRect2 = {33, 0, 31, 31};
const SDL_Rect cowRect3 = {65, 0, 31, 31};

const std::string cowFilePath = {"cow.png"};

const double cowRatio = 7;




const SDL_Rect iconDefaultRect = {0, 0, 128, 128};
const SDL_Rect iconClickedRect = {0, 128, 128, 128};

const double iconRatio = 0.5;

const VectorMath musicIconPos = {SCREEN_WIDTH - 128 * iconRatio, 0};






const std::string menuPlayButtonFilePath = {"playButton.png"}; //play
const std::string menuGameButtonFilePath = {"gameButton.png"}; //story
const std::string menuInforButtonFilePath = {"informationButton.png"}; //how to play
const std::string menuAboutButtonFilePath = {"aboutButton.png"}; //credit
const std::string backButtonFilePath = {"backButton.png"};
const std::string musicIconFilePath = {"musicIcon.png"};

const std::string menuBackground = {"menuBackground.png"};
const std::string storyBackground = {"story.png"}; //game
const std::string instructionBackground = {"instruction.png"}; //infor
const std::string creditBackground = {"credit.png"}; //about

const VectorMath menuPlayButtonPos = {100, 100};
const VectorMath menuGameButtonPos = {100, 200};
const VectorMath menuInforButtonPos = {100, 300};
const VectorMath menuAboutButtonPos = {100, 400};
const VectorMath rootPos = {0, 0};

const SDL_Rect fullScreenRect = {0, 0, 800, 600};

const double fullScreenRatio = 1;
const double buttonRatio = 1.5;
const double backButtonRatio = 1;






const bool TRUE = true;
const bool FALSE = false;

const std::string utilsFilePath = {"Utils.png"};
const std::string numbersFilePath = {"Numbers.png"};
const std::string scoreFilePath = {"Score.png"};
const std::string gameOverFilePath = {"GameOver.png"};

const SDL_Rect livesRect = {0, 34, 16, 13};
const double livesWitdth = 16;
const double livesRatio = 3.5;
const SDL_Rect deadRect = {32, 34, 16, 13};
const SDL_Rect scoreRect = {0, 0, 240, 120};
const SDL_Rect gameOverRect = {0, 0, 240, 120};

const double numRatio = 1.75;
const double scoreRatio = 1.5;
const double gameOverRatio = 1.5;

const double alignLives_screen = (SCREEN_WIDTH - rightDropBorder - boulderWidth * boulderRatio) / 3; // ?

const int MAX_LIVES = 3;





const double buffRatio = 2;
const SDL_Rect shieldRect = {16, 16, 16, 16};
const double MAX_BUFF_HEIGHT = 16;
const double MAX_BUFF_WIDTH = 16;

const double debuffRatio = 4;
const double MAX_DEBUFF_HEIGHT = 10;
const double MAX_DEBUFF_WIDTH = 16;


