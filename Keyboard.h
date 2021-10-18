#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

// キーの入力状態を更新する
void Keyboard_Update();

// 引数のキーコードのキーの入力状態を返す
int Keyboard_Get(int KeyCode);

#endif // _KEYBOARD_H_