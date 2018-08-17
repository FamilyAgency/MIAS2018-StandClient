import QtQuick 2.2
import QtQuick.Controls.Styles 1.4

Item
{
    anchors.fill: parent;

    property var isRunning;
    property var isPreTaskState;
    property var completedPath;
    property var uncompletedPath;
    property var currentPoint;
    property var startPoint;
    property bool isDrawCircles: false;
    property var circles;
    property bool isSuperGame: false;

    Canvas
    {
        id: canvas;
        anchors.fill: parent;
        antialiasing: true;
        smooth: true;

        onPaint:
        {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            if(isPreTaskState || isRunning)
            {
                if(isSuperGame)
                {
                    drawSuperGameGuidePaths(ctx);
                    return;
                }

                drawGuidePaths(ctx);
                var list = completedPath;

                ctx.lineWidth = consts.lineWidth * 0.6;
                ctx.strokeStyle = "#797e84";
                ctx.lineCap = consts.lineCap;
                ctx.lineJoin = consts.lineJoin;

                var curPoint = currentPoint;
                if(list.length > 1)
                {
                    ctx.beginPath();
                    ctx.moveTo(list[0].x, list[0].y);
                    for(var i = 1; i < list.length; i++)
                    {
                        ctx.lineTo(list[i].x, list[i].y);
                    }

                    ctx.lineTo(curPoint.x, curPoint.y);
                    ctx.stroke();
                    ctx.closePath();
                }
                else
                {
                    ctx.beginPath();
                    ctx.moveTo(startPoint.x, startPoint.y );
                    ctx.lineTo(curPoint.x, curPoint.y);
                    ctx.stroke();
                    ctx.closePath();
                }

                if(isDrawCircles)
                {
                    drawCircles(ctx);
                    drawFlag(ctx);
                }
            }
        }
    }

    OpacityAnimator on opacity
    {
        id: opacityAnim;
        from: 0;
        to: 1;
        duration: 700;
        running: false;
        easing.type: "InOutCubic";
    }

    function show()
    {
        opacity = 0;
        opacityAnim.start();
    }

    function draw()
    {
        canvas.requestPaint();
    }

    function drawSuperGameGuidePaths(ctx)
    {
        var list = uncompletedPath;

        ctx.beginPath();
        ctx.moveTo(list[0].x, list[0].y);
        ctx.strokeStyle =  "#ff0000";
        ctx.lineWidth = consts.lineWidth;

        for(var i = 1; i < list.length; i++)
        {
            ctx.lineTo(list[i].x, list[i].y);
        }

        ctx.stroke();
        ctx.closePath();
    }

    function drawGuidePaths(ctx)
    {
        var list = uncompletedPath;

        ctx.beginPath();
        ctx.moveTo(currentPoint.x, currentPoint.y);
        ctx.strokeStyle =  "#ff0000";
        ctx.lineWidth = consts.lineWidth;

        for(var i = 0; i < list.length; i++)
        {
            ctx.lineTo(list[i].x, list[i].y);
        }

        ctx.stroke();
        ctx.closePath();
    }

    function drawCircles(ctx)
    {
        for(var k = 0; k < circles.length - 1; k++)
        {
            ctx.beginPath();
            ctx.fillStyle =  "#ffffff";
            ctx.strokeStyle =  "#ff0000";
            ctx.lineWidth = 18;
            var ellipseSize = 20;
            ctx.ellipse(circles[k].x - ellipseSize * 0.5, circles[k].y - ellipseSize * 0.5, ellipseSize, ellipseSize);
            ctx.stroke();
            ctx.fill();
            ctx.closePath();
        }
    }

    function drawFlag(ctx)
    {
        var k = circles.length - 1;
        ctx.beginPath();
        ctx.fillStyle =  "#ffffff";
        ctx.strokeStyle =  "#ff0000";
        ctx.lineWidth = 21;
        var ellipseSize = 35;
        ctx.ellipse(circles[k].x - ellipseSize * 0.5, circles[k].y - ellipseSize * 0.5, ellipseSize, ellipseSize);
        ctx.stroke();
        ctx.fill();
        ctx.closePath();
    }
}
