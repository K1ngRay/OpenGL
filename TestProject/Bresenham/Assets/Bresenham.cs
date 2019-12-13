using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class Bresenham : MonoBehaviour {

    // Use this for initialization
    public Transform cube1;
    public Transform cube2;
    public Transform cube3;

    [Header("Line")]
    public Vector2 oriVec2;
    public Vector2 FinVec2;

    [Header("Ploygon")]
    public List<Point> points;

    private Transform curCube;
	void Start () {
        //Func1();
        //Func2();
        //Func3();
        //DrawBG();
        DrawPolygon();
    }

    private void Update()
    {
        LinkPoint(points, 0);
    }

    /// <summary>
    /// Bresenham
    /// </summary>
    void Func1()
    {
        Transform parent = GameObject.Find("Cube1").transform;
        Vector2 vec2 = oriVec2;
        float k = (FinVec2.y - oriVec2.y) / (FinVec2.x - oriVec2.x);
        float d = 0.5f - k;
        while ((int)(vec2.x)!=(int)FinVec2.x)
        {
            curCube = Instantiate(cube1, vec2, Quaternion.identity, parent);
            vec2.x += 1;
            if (d<0)
            {
                d = d + 1 - k;
                vec2.y += 1;
            }
            else
            {
                d = d - k;
            }
        }
    }

    /// <summary>
    /// 优化浮点数的Bresenham
    /// </summary>
    void Func2()
    {
        Transform parent = GameObject.Find("Cube2").transform;
        Vector2 vec2 = oriVec2;
        int deltaY = (int)(FinVec2.y - oriVec2.y);
        int deltaX = (int)(FinVec2.x - oriVec2.x);
        int d = deltaX - 2 * deltaY;
        while ((int)(vec2.x) != (int)FinVec2.x)
        {
            curCube = Instantiate(cube2, new Vector3(vec2.x,vec2.y,2f), Quaternion.identity,parent);
            vec2.x += 1;
            if (d < 0)
            {
                d = d + 2 * deltaX - 2 * deltaY;
                vec2.y += 1;
            }
            else
            {
                d = d - 2 * deltaY;
            }
        }
    }

    /// <summary>
    /// 改进的BresenHam
    /// </summary>
    void Func3()
    {
        Transform parent = GameObject.Find("Cube3").transform;
        Vector2 vec2 = oriVec2;
        int deltaX = (int)(FinVec2.x - oriVec2.x);
        int deltaY = (int)(FinVec2.y - oriVec2.y);
        int e = -deltaX;
        while ((int)(vec2.x) != (int)FinVec2.x)
        {
            curCube = Instantiate(cube3, new Vector3(vec2.x, vec2.y, 4f), Quaternion.identity,parent);
            vec2.x += 1;
            e += 2 * deltaY;
            if (e > 0)
            {
                e -= 2 * deltaX;
                vec2.y += 1;
            }
        }
    }

    void DrawBG()
    {
        Transform parent = GameObject.Find("BG").transform;
        int deltaX = (int)(FinVec2.x - oriVec2.x);
        int deltaY = (int)(FinVec2.y - oriVec2.y);

        for (int i = 0; i < deltaX; i++)
        {
            for (int j = 0; j < deltaY; j++)
            {
                Instantiate(cube1, new Vector3(i,j,6f), Quaternion.identity,parent);
            }
        }
    }

    void DrawPolygon()
    {
        Transform parent = GameObject.Find("Cube1").transform;
        VectorTwo rangeX = new VectorTwo(int.MaxValue,-1);
        VectorTwo rangeY = new VectorTwo(int.MaxValue,-1);
        List<Point> points = new List<Point>(this.points);
        //计算背景
        for (int i = 0; i < points.Count; i++)
        {
            if (points[i].xy.x<rangeX.x)
                rangeX.x = points[i].xy.x;
            if (points[i].xy.x >rangeX.y)
                rangeX.y = points[i].xy.x;
            if (points[i].xy.y <rangeY.x)
                rangeY.x = points[i].xy.y;
            if (points[i].xy.y > rangeY.y)
                rangeY.y = points[i].xy.y;
            Instantiate(cube3, new Vector3(points[i].xy.x, points[i].xy.y,0f), Quaternion.identity, parent);
        }
        

        //绘制背景
        parent = GameObject.Find("BG").transform;
        for (int i = (int)rangeX.x; i <= (int)rangeX.y; i++)
        {
            for (int j = (int)rangeY.x; j <= rangeY.y; j++)
            {
                Instantiate(cube1, new Vector3(i, j, 6f), Quaternion.identity, parent);
            }
        }

        points.Sort(PointsSort);
        //创建桶结点
        Dictionary<float, List<BucketNode>> dic = new Dictionary<float, List<BucketNode>>();
        for (int i = 0; i < points.Count; i++)
        {
            for (int j = 0; j < points[i].xy.weight; j++)
            {
                BucketNode node = new BucketNode();
                Point point = points[i];
                node.x = point.xy.x;
                if (j==1)
                {
                    node.yMax = point.rightNode.y - 1;
                    node.delta = 1f / ((point.rightNode.y - point.xy.y) / (point.rightNode.x - point.xy.x));
                }
                else
                {
                    node.yMax = point.leftNode.y - 1;
                    node.delta = 1f / ((point.leftNode.y - point.xy.y) / (point.leftNode.x - point.xy.x));
                }
                if (!dic.ContainsKey(point.xy.y))
                {
                    dic.Add(point.xy.y, new List<BucketNode>());
                    dic[point.xy.y].Add(node);
                }
                else
                    dic[point.xy.y].Add(node);
            }
        }
        foreach (var item in dic)
        {
            item.Value.Sort(BucketsSort);
            LinkNode(item.Value, 0);
        }

        List<BucketNode> vaildList = new List<BucketNode>();
        //绘制多边形
        parent = GameObject.Find("Cube2").transform;
        int minY = (int)rangeY.x;
        int maxY = (int)rangeY.y;
        for (int i = minY; i <= maxY; i++)
        {
            if (dic.ContainsKey(i))
            {
                vaildList.AddRange(dic[i]);
                vaildList.Sort(BucketsSort);
            }
            for (int j = 0; j < vaildList.Count; j += 2)
            {
                int min = Mathf.RoundToInt(vaildList[j].x);
                int max = Mathf.RoundToInt(vaildList[j + 1].x);
                for (int k = min; k <= max; k++)
                {
                    Instantiate(cube2, new Vector3(k, i, 0f), Quaternion.identity, parent);
                }
                BucketNode DeleteFir = null;
                BucketNode DeleteSec = null;
                if ((int)vaildList[j].yMax == i)
                    DeleteFir = vaildList[j];
                else
                    vaildList[j].x += vaildList[j].delta;
                if ((int)vaildList[j + 1].yMax == i)
                    DeleteSec = vaildList[j + 1];
                else
                    vaildList[j + 1].x += vaildList[j + 1].delta;

                if (DeleteFir != null)
                {
                    vaildList.Remove(DeleteFir);
                    j--;
                }
                if (DeleteSec != null)
                {
                    vaildList.Remove(DeleteSec);
                    j--;
                }
            }
        }
    }

    int PointsSort(Point x,Point y)
    {
        int value = x.xy.y.CompareTo(y.xy.y);
        return value;
    }

    int BucketsSort(BucketNode x, BucketNode y)
    {
        int value = x.x.CompareTo(y.x);
        if (value == 0)
            value = x.delta.CompareTo(y.delta);
        return value;
    }

    void LinkNode(List<BucketNode> list,int index)
    {
        if (index >= list.Count - 1) return;

        list[index].next = list[index + 1];
        LinkNode(list, index + 1);
    }

    void LinkPoint(List<Point> list,int index)
    {        
        if (index >= list.Count-1)
        {
            Vector3 start = new Vector3(list[index].xy.x, list[index].xy.y, -1f);
            Vector3 end = new Vector3(list[0].xy.x, list[0].xy.y, -1f);
            Debug.DrawLine(start, end, Color.yellow);
        }
        else
        {
            Vector3 start = new Vector3(list[index].xy.x, list[index].xy.y, -1f);
            Vector3 end = new Vector3(list[index + 1].xy.x, list[index + 1].xy.y, -1f);
            Debug.DrawLine(start, end, Color.yellow);
            LinkPoint(list, index + 1);
        }
    }

    [Serializable]
    public struct Point
    {
        public VectorTwo xy;
        public VectorTwo leftNode;
        public VectorTwo rightNode;
    }

    /// <summary>
    /// 边表
    /// </summary>
    struct EdgeTable
    {
        public int y;
        public BucketNode first;
    }

    /// <summary>
    /// 桶表
    /// </summary>
    class BucketNode
    {
        public float x;
        public float yMax;
        public float delta;
        public BucketNode next;
    }

    [Serializable]
    public struct VectorTwo
    {
        public float x;
        public float y;
        [Range(0,2)]
        public int weight;

        public VectorTwo(float x, float y)
        {
            this.x = x;
            this.y = y;
            weight = 0;
        }

        public VectorTwo(float x, float y , int weight)
        {
            this.x = x;
            this.y = y;
            this.weight = weight;
        }
    }
}
