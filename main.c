#include <raylib.h>
#include <stdint.h>
#include <malloc.h>

int main(int argc, char** argv){
  uint8_t FPS = 144;
  const uint16_t WINW = 600;
  const uint16_t WINH = 400;
  const float DEFAULT_VOLUME = 0.2f;
  const float DELTA_VOLUME = 0.1f;
  float volume = DEFAULT_VOLUME;
  const Color BG_COLOR = {30, 31, 33, 1};
  char* songName= argv[1];

  InitWindow(WINW, WINH, "Player");
  SetTargetFPS(FPS);
  Texture LOGO = LoadTexture("logo.png");

  InitAudioDevice();
  Music music = LoadMusicStream(argv[1]);
  PlayMusicStream(music);
  SetMusicVolume(music, DEFAULT_VOLUME);

  while (!WindowShouldClose()) {
    if (IsFileDropped()){
      FilePathList droppedFiles = LoadDroppedFiles();
      char* file_path = droppedFiles.paths[0];
      StopMusicStream(music);
      UnloadMusicStream(music);
      music = LoadMusicStream(file_path);
      PlayMusicStream(music);
      SetMusicVolume(music, volume);
      
      UnloadDroppedFiles(droppedFiles);
    }
    UpdateMusicStream(music);

    if(IsKeyPressed(KEY_SPACE)){
      if(IsMusicStreamPlaying(music))
        PauseMusicStream(music);
      else
       ResumeMusicStream(music);
    }
    else if (IsKeyPressed(KEY_VOLUME_DOWN) || IsKeyPressed(KEY_DOWN)) {
      if (volume >=DELTA_VOLUME) {
        volume-=DELTA_VOLUME;
      }
      else {
        volume = 0;
      }
      SetMusicVolume(music, volume);
    }
    else if (IsKeyPressed(KEY_VOLUME_UP) || IsKeyPressed(KEY_UP)) {
      if (volume <=1-DELTA_VOLUME){
        volume+=DELTA_VOLUME;
      }
      else {
        volume = 1;
      }
      SetMusicVolume(music, volume);
    }
    else if (IsKeyPressed(KEY_X)) {
      CloseWindow();
    }

    BeginDrawing();
    ClearBackground(BG_COLOR);
    DrawFPS(5, 5);
    DrawTexture(LOGO, WINW/2-LOGO.width/2, WINH/2-LOGO.height/2, WHITE);
    DrawText("UP - +vol\nDOWN - -vol\nSPACE - stop/resume\nx - exit\n --Use drag n\' drop", 5, 300, 20, LIGHTGRAY);
    EndDrawing();
  }
  
  return 0;
}
