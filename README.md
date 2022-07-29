# VTK_FILTER

# コーディング規約
コーディング規約はKVSライブラリに則ること。
[KVS CodingConvention](https://github.com/naohisas/KVS/wiki/CodingConvention)
## スタイル規約
* 字下げ

  半角スペース4文字で表現すること。
  switch文内のcaseやdefaultのラベル、クラスのメンバ変数やメソッドのアクセス属性を指定するprivate,protected,publicの修飾子は字下げしない。
  ```
  //Good
  void Func()
  {
      const int n = 10;
      for( int i = 0; i < n; i++ )
      {
          DoSomething();
      }
  }

  switch( x )
  {
  case y:
      break;
  default:
      break;
  }

  class ClassName
  {
  public:
      ClassName();
  };
  ```

* 中括弧の位置

    制御文の後ろではなくその次の行に改行しすること。
  ```
  //Good
  if( x == y )
  {
      DoSomething();
  }

  for ( int i = 0; i < n; i++ )
  {
     DoSomething();
  }

  class ClassName
  {
  public:
      ClassName();
  };

  void FuncName()
  {
      DoSomething();
  }
  ```

* 制御文の括弧の位置
  ```
  // Good
  if ( x == y )
  for ( int i = 0; i < n; i++ )
  while ( x < y )
  ```

* return文の括弧

  ```
  //Good
  return x;
  ```

* 引数なしの関数定義
  ```
  //Good
  void Func()
  {
      DoSomething();
  }
  ```

* 初期化リスト
  ```
  // Good
  ClassName::ClassName( int param1, int param2, int param3 ):
      m_param1( param1 ),
      m_param2( param2 ),
      m_param3( param3 )
  {
      DoSomething();
  }
  ```

----
## 命名規則
* クラス名
 
  クラス名は名前を構成する各単語は大文字で開始すること(Upper Camel Case)
  クラス名は原則として名詞で表現して省略形を避け役割がわかる名前にすること。
  ```
  ClassName
  VolumeRenderer
  ``` 

* メンバ変数名

  クラスを構成するメンバ変数の名前は先頭にm_を付け、単語間に下線を付けること。
  メンバ変数も、クラス名と同じく省略形を避け、意味がわかる名前にすること。
  ```
  m_member_variable
  m_sampling_step
  ```

* メソッド名(publicおよびprotected属性)

  public属性およびprotected属性を持つメソッドの名前は、先頭は小文字としてそれ以降の単語は大文字で開始すること。(lower Camel Case)
  ```
  methodName
  ```

* メソッド名(private属性)

  private属性を持つメソッドの名前は原則、各単語を小文字で開始しかつ単語間に下線を付けること。
  ```
  method_name
  ```

* 関数名および静的メソッド名

  関数名は名前を構成する各単語は大文字で開始すること。(Upper Camel Case)
  また静的メソッドについてもクラスのインスタンスを作成することなく通常の関数と同じような役割を果たすため、関数名と同様の命名規則を適用する。
  ```
  FunctionName
  StaticMethodName
  ```

* マクロ名
  
  マクロ名は全て大文字とし、先頭にPBVR_FILTERを付け、単語間には下線を付けることとする。
  ```
  PBVR_FILTER_MACRO_NAME
  ```

----
## プログラミング規約
* メンバ変数の定義

  クラスのメンバ変数は原則としてprivate属性を付けて定義することとする。
  ```
  private:
      int m_x;
      int m_y;
  ```
  
* 基本型の引数

  intやfloatなどの基本型(プリミティブ型)の値を入力として渡す場合は、それが入力値でありかつ変更が許されない値であることを明示するためにconst属性を記述すること。
  ```
  void Func( const int x )
  ```

* ポイント渡しと参照渡し

  比較的大きなクラスまたは構造体を関数(メソッド)の引数とて渡す場合は、それが入力である場合はconst属性を付けて参照渡しとし、出力または入出力である場合はポインタ渡しとする。
  ```
  void Func( const ClassA& input, ClassB* output1, ClassC* input_out_put )
  ```

* インクルードガード
  
  ```
  #ifndef KVS__NAMESPACE__FILE_NAME_H_INCLUDE
  #define KVS__NAMESPACE__FILE_NAME_H_INCLUDE
  ...
  #endif

  #ifndef KVS__FILE_NAME_H_INCLUDE
  #define KVS__FILE_NAME_H_INCLUDE
  ...
  #endif
  ```
