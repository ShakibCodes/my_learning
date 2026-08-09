# Flutter
Flutter is a framework of dart programming langauge which helps you with making the UI/UX with cross platform native support meaning One codebase works on all Os/platform like One codebase works with Android, IOS, Windows, MacOS and more.

## Basic syntax (Snippet)
```cpp
import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(body: Center(child: Text('Hello, World!'))),
    );
  }
}
```

> It imports material UI by writing <br> `import 'package:flutter/material.dart';` at the top

### It has Certain Styling properties which will be added inside this block of code:

```cpp
import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        body: Center(child: Text(
            'Hello, World!',

            //here comes all of your styling properties of text
            
            ))),
    );
  }
}
```

### and here's some styling properties of text:

1. fontSize