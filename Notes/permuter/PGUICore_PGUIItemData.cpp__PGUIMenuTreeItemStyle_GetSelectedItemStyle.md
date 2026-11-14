# Permuter: PGUIMenuTreeItemStyle::GetSelectedItemStyle in Src\PGUICore\PGUIItemData.cpp

Started 2026-11-13 16:26, seed None, 30 rounds x 20 variants. Score: bytes without a counterpart in the original (0 = exact). An exact result is a candidate until a normal build round verifies it.

Start (unchanged file): score 9
- round   1: 3 variants, best of round 9, best so far 9
Round 2: no new rewrites left - stopped.

Tried 4 variants (0 did not compile). Best score 9.

### score 9: swap operands

```diff
--- current
+++ variant
@@ -1,4 +1,4 @@
 
-    if (level == 0 || level == 1) {
+    if (level == 0 || 1 == level) {
         return m_pCurrentItemSelectedStyle;
     }
```

### score 9: swap operands

```diff
--- current
+++ variant
@@ -1,4 +1,4 @@
 
-    if (level == 0 || level == 1) {
+    if (0 == level || level == 1) {
         return m_pCurrentItemSelectedStyle;
     }
```

### score 9: swap operands; swap operands

```diff
--- current
+++ variant
@@ -1,4 +1,4 @@
 
-    if (level == 0 || level == 1) {
+    if (0 == level || 1 == level) {
         return m_pCurrentItemSelectedStyle;
     }
```

