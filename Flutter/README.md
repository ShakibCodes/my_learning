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

## 🎨 Flutter TextStyle Properties

| Property | Example | What it does |
|---|---|---|
| `fontSize` | `fontSize: 30` | Changes text size |
| `fontWeight` | `FontWeight.bold` | Makes text bold/thin |
| `fontStyle` | `FontStyle.italic` | Makes text italic |
| `color` | `color: Colors.red` | Changes text color |
| `fontFamily` | `fontFamily: 'Arial'` | Changes font |
| `letterSpacing` | `letterSpacing: 2` | Space between letters |
| `wordSpacing` | `wordSpacing: 5` | Space between words |
| `height` | `height: 1.5` | Controls line height |
| `decoration` | `TextDecoration.underline` | Underline/strike/overline |
| `decorationColor` | `Colors.red` | Changes decoration color |
| `decorationStyle` | `TextDecorationStyle.dashed` | Solid/dashed/dotted/wavy |
| `decorationThickness` | `2` | Changes decoration thickness |
| `backgroundColor` | `Colors.yellow` | Background behind text |
| `shadows` | `[Shadow(...)]` | Adds shadow to text |

### Font Weight

| Value | Meaning |
|---|---|
| `FontWeight.w100` | Very thin |
| `FontWeight.w200` | Extra light |
| `FontWeight.w300` | Light |
| `FontWeight.w400` | Normal |
| `FontWeight.w500` | Medium |
| `FontWeight.w600` | Semi-bold |
| `FontWeight.w700` | Bold |
| `FontWeight.w800` | Extra-bold |
| `FontWeight.w900` | Black / heaviest |

### Text Decoration

| Value | Result |
|---|---|
| `TextDecoration.underline` | Underline |
| `TextDecoration.overline` | Line above text |
| `TextDecoration.lineThrough` | Strike-through |
| `TextDecoration.none` | No decoration |

### Text Decoration Style

| Value | Style |
|---|---|
| `TextDecorationStyle.solid` | Solid |
| `TextDecorationStyle.double` | Double line |
| `TextDecorationStyle.dotted` | Dotted |
| `TextDecorationStyle.dashed` | Dashed |
| `TextDecorationStyle.wavy` | Wavy |

### Example

```dart
Text(
  'This is Shakib',
  style: TextStyle(
    fontSize: 30,
    fontWeight: FontWeight.bold,
    fontStyle: FontStyle.italic,
    color: Colors.blue,
    fontFamily: 'Arial',
    letterSpacing: 2,
    wordSpacing: 5,
    decoration: TextDecoration.underline,
    decorationColor: Colors.red,
    decorationStyle: TextDecorationStyle.wavy,
    decorationThickness: 2,
    backgroundColor: Colors.yellow,
  ),
)