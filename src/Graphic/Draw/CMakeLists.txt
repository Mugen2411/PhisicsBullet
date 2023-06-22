cmake_minimum_required(VERSION 3.11)
add_library(Draw STATIC
 CDrawCircleGauge.h CDrawCircleGauge.cpp CDrawExtendWithBlend.h CDrawExtendWithBlend.cpp
 CDrawGraphFReserve.h CDrawGraphFReserve.cpp CDrawGraphReserve.h CDrawGraphReserve.cpp
 CDrawModiGraphReserve.h CDrawModiGraphReserve.cpp 
 CDrawRectGraphWithBlendReserve.h CDrawRectGraphWithBlendReserve.cpp
 CDrawRotaGraphFReserve.h CDrawRotaGraphFReserve.cpp 
 CDrawRotaGraphFwithBlendReserve.h CDrawRotaGraphFwithBlendReserve.cpp
 CDrawRotaGraphReserve.h CDrawRotaGraphReserve.cpp CNumberDrawer.h CNumberDrawer.cpp 
 CRenderReserveList.h CRenderReserveList.cpp CTextDrawer.h CTextDrawer.cpp IRenderReserve.h IRenderReserve.cpp
)