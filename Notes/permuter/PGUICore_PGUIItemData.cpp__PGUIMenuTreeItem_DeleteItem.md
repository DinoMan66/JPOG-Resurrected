# Permuter: PGUIMenuTreeItem::DeleteItem in Src\PGUICore\PGUIItemData.cpp

Started 2026-11-13 16:26, seed None, 30 rounds x 20 variants. Score: bytes without a counterpart in the original (0 = exact). An exact result is a candidate until a normal build round verifies it.

Start (unchanged file): score 3
- round   1: 1 variants, best of round 20, best so far 3
Round 2: no new rewrites left - stopped.

Tried 2 variants (0 did not compile). Best score 3.

### score 20: swap statements

```diff
--- current
+++ variant
@@ -1,5 +1,5 @@
 
+    m_oChildren.Remove(item);
     item->m_pParent = 0;
-    m_oChildren.Remove(item);
     delete item;
 
```

