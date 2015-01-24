from cv2 import *
import numpy as np

def tracking(fast):
    color = np.random.randint(0, 255, (100,3))
    _, prev = video.read()
    prevGray = cvtColor(prev, COLOR_BGR2GRAY)

    fourcc = cv.CV_FOURCC(*'DIVX')
    filename = 'fast.avi' if fast else 'harris.avi'
    out = VideoWriter(filename, fourcc, 20.0, prevGray.shape)

    pointsPrev = detect(prevGray, fast)
    
    mask = np.zeros_like(prev)
    while(video.isOpened()):
        ret, curr = video.read()
        if not ret:
            break
        currGray = cvtColor(curr, COLOR_BGR2GRAY)

        pointsCurr, status, _ = calcOpticalFlowPyrLK( prevImg = prevGray,
                                                      nextImg = currGray,
                                                      prevPts = pointsPrev, 
                                                      nextPts = None, 
											          winSize  = (10, 10),
                                                      maxLevel = 2,
                                                      criteria = (TERM_CRITERIA_EPS | TERM_CRITERIA_COUNT, 10, 0.03)
                                                      )

        for i, (new, old) in enumerate(zip(pointsCurr, pointsPrev)):
            a, b = new.ravel()
            c, d = old.ravel()
            clr = color[i % 100].tolist()
            line(mask, (a, b), (c, d), clr, 2)
            circle(curr, (a, b), 3, clr, -1)
        
        img = add(curr, mask)
        out.write(img)
        prevGray = currGray
        pointsPrev = pointsCurr
    
    return out

def detect(frame, fast):
    if not fast:
        return goodFeaturesToTrack( frame,                  # img
                                    500,                    # maxCorners
                                    0.03,                   # qualityLevel
                                    10,                     # minDistance
                                    None,                   # corners, 
                                    None,                   # mask, 
                                    2,                      # blockSize, 
                                    useHarrisDetector=True, # useHarrisDetector, 
                                    k=0.04                  # k
                                    )
    else:
        Fast = FastFeatureDetector(125, FAST_FEATURE_DETECTOR_TYPE_9_16)
        kp = Fast.detect(frame, None)
        return np.array([np.float32( np.array([np.array(x.pt)])) for x in kp])

video = VideoCapture('sequence.avi')
vid = tracking(True)

video = VideoCapture('sequence.avi')
vid = tracking(False)

waitKey(0)