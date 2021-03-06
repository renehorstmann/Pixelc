#include "brushshape.h"

struct BrushShapeGlobals_s brushshape = {{
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 1, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 1, 1, 0, 0},
                                                          {0, 0, 0, 1, 1, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 1, 0, 0, 0},
                                                          {0, 0, 1, 1, 1, 0, 0},
                                                          {0, 0, 0, 1, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 1, 1, 1, 0, 0},
                                                          {0, 0, 1, 1, 1, 0, 0},
                                                          {0, 0, 1, 1, 1, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 1, 1, 0, 0},
                                                          {0, 0, 1, 1, 1, 1, 0},
                                                          {0, 0, 1, 1, 1, 1, 0},
                                                          {0, 0, 0, 1, 1, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 1, 0, 0, 0},
                                                          {0, 0, 1, 1, 1, 0, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 0, 1, 1, 1, 0, 0},
                                                          {0, 0, 0, 1, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 1, 1, 1, 1, 0},
                                                          {0, 0, 1, 1, 1, 1, 0},
                                                          {0, 0, 1, 1, 1, 1, 0},
                                                          {0, 0, 1, 1, 1, 1, 0},
                                                          {0, 0, 0, 0, 0, 0, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 1, 1, 1, 0, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 0, 1, 1, 1, 0, 0},
                                                          {0, 0, 0, 0, 0, 0, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 0, 1, 1, 0, 0},
                                                          {0, 0, 1, 1, 1, 1, 0},
                                                          {0, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 1},
                                                          {0, 0, 1, 1, 1, 1, 0},
                                                          {0, 0, 0, 1, 1, 0, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 0, 0, 0, 0, 0, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 1, 0, 0, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 0, 0, 1, 0, 0, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 0, 1, 1, 1, 1, 0},
                                                          {0, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 1},
                                                          {0, 0, 1, 1, 1, 1, 0}
                                                  },
                                                  {
                                                          {0, 0, 0, 0, 0, 0, 0},
                                                          {0, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 1}
                                                  },
                                                  {
                                                          {0, 0, 1, 1, 1, 0, 0},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {0, 0, 1, 1, 1, 0, 0}
                                                  },
                                                  {
                                                          {0, 1, 1, 1, 1, 1, 0},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {0, 1, 1, 1, 1, 1, 0}
                                                  },
                                                  {
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1},
                                                          {1, 1, 1, 1, 1, 1, 1}
                                                  }

                                          }};
