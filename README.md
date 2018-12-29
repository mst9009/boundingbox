# universal-boundingbox
旨在提供一个通用的BoundingBox访问接口

在写入时，可按照以下任一方式
    CORNER_CORNER mode: xmin,ymin,xmax,ymax
    CORNER_SIZE mode: xmin,ymin,width,height
    CENTROID_SIZE mode: xcentroid,ycentroid,width,height
设置BoundingBox的矩形位置，同时设置BoundingBox对应的mode值

在访问时，只需根据需要调用对应的接口，而无需关心BoundingBox是如何写入的
