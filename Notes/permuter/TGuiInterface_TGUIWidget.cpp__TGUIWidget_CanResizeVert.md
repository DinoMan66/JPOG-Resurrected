# Permuter: TGUIWidget::CanResizeVert in Src\TGuiInterface\TGUIWidget.cpp

Started 2026-11-13 16:26, seed None, 30 rounds x 20 variants. Score: bytes without a counterpart in the original (0 = exact). An exact result is a candidate until a normal build round verifies it.

Start (unchanged file): score 11
- round   1: 7 variants, best of round 11, best so far 11
Round 2: no new rewrites left - stopped.

Tried 8 variants (0 did not compile). Best score 11.

### score 11: swap operands

```diff
--- current
+++ variant
@@ -1,4 +1,4 @@
 
-    if (m_eSizeModeVert != SIZE_MODE_0) {
+    if (SIZE_MODE_0 != m_eSizeModeVert) {
         if (m_eSizeModeVert != SIZE_MODE_2) {
             return false;
```

### score 11: swap operands

```diff
--- current
+++ variant
@@ -4,5 +4,5 @@
             return false;
         }
-        if (m_pParent != 0 && m_pParent->GetLayoutManager() != 0) {
+        if (0 != m_pParent && m_pParent->GetLayoutManager() != 0) {
             return false;
         }
```

### score 11: swap operands; swap operands

```diff
--- current
+++ variant
@@ -1,8 +1,8 @@
 
     if (m_eSizeModeVert != SIZE_MODE_0) {
-        if (m_eSizeModeVert != SIZE_MODE_2) {
+        if (SIZE_MODE_2 != m_eSizeModeVert) {
             return false;
         }
-        if (m_pParent != 0 && m_pParent->GetLayoutManager() != 0) {
+        if (0 != m_pParent && m_pParent->GetLayoutManager() != 0) {
             return false;
         }
```

### score 11: swap operands

```diff
--- current
+++ variant
@@ -1,5 +1,5 @@
 
     if (m_eSizeModeVert != SIZE_MODE_0) {
-        if (m_eSizeModeVert != SIZE_MODE_2) {
+        if (SIZE_MODE_2 != m_eSizeModeVert) {
             return false;
         }
```

### score 11: swap operands; swap operands

```diff
--- current
+++ variant
@@ -1,8 +1,8 @@
 
-    if (m_eSizeModeVert != SIZE_MODE_0) {
+    if (SIZE_MODE_0 != m_eSizeModeVert) {
         if (m_eSizeModeVert != SIZE_MODE_2) {
             return false;
         }
-        if (m_pParent != 0 && m_pParent->GetLayoutManager() != 0) {
+        if (0 != m_pParent && m_pParent->GetLayoutManager() != 0) {
             return false;
         }
```

