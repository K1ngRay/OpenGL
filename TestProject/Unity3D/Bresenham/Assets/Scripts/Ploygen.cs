using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class Ploygen : MonoBehaviour {

    [Serializable]
    public struct VectorTwo
    {
        public float x;
        public float y;
        [Range(0, 2)]
        public int weight;

        public VectorTwo(float x, float y)
        {
            this.x = x;
            this.y = y;
            weight = 0;
        }

        public VectorTwo(float x, float y, int weight)
        {
            this.x = x;
            this.y = y;
            this.weight = weight;
        }
    }

    [Serializable]
    public class Point
    {
        public VectorTwo xy;
        public VectorTwo leftNode;
        public VectorTwo rightNode;
    }

    /// <summary>
    /// 桶表
    /// </summary>
    class BucketNode
    {
        public float x;
        public float yMax;
        public float delta;
    }

    public Transform cube1;
    public Transform cube2;
    public Transform cube3;

    [Header("Ploygon")]
    public List<Point> points;

    void Start () {
        DrawPolygon();
    }
	
    private void OnDrawGizmos()
    {
        for (int i = 0; i < points.Count; i++)
        {
            Gizmos.DrawCube(new Vector3(points[i].xy.x, points[i].xy.y, -1f), Vector3.one);
        }
        LinkPoint(points, 0);
    }


    void LinkPoint(List<Point> list, int index)
    {
        if (index >= list.Count - 1)
        {
            Vector3 start = new Vector3(list[index].xy.x, list[index].xy.y, -1f);
            Vector3 end = new Vector3(list[0].xy.x, list[0].xy.y, -1f);
            Debug.DrawLine(start, end, Color.yellow);

            list[index].leftNode = list[0].xy;
            list[index].rightNode = list[index - 1].xy;
        }
        else
        {
            Vector3 start = new Vector3(list[index].xy.x, list[index].xy.y, -1f);
            Vector3 end = new Vector3(list[index + 1].xy.x, list[index + 1].xy.y, -1f);
            Debug.DrawLine(start, end, Color.yellow);

            list[index].leftNode = list[index + 1].xy;
            if (index==0)
            {
                list[index].rightNode = list[list.Count - 1].xy;
            }
            else
            {
                list[index].rightNode = list[index - 1].xy;
            }

            LinkPoint(list, index + 1);            
        }
        list[index].xy.weight = 0;
        if (list[index].leftNode.y>list[index].xy.y)
        {
            list[index].xy.weight++;
        }
        if (list[index].rightNode.y > list[index].xy.y)
        {
            list[index].xy.weight++;
        }
    }

    int PointsSort(Point x, Point y)
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

    void DrawPolygon()
    {
        Transform parent = GameObject.Find("Cube1").transform;
        VectorTwo rangeX = new VectorTwo(int.MaxValue, -1);
        VectorTwo rangeY = new VectorTwo(int.MaxValue, -1);
        List<Point> points = new List<Point>(this.points);
        //计算背景
        for (int i = 0; i < points.Count; i++)
        {
            if (points[i].xy.x < rangeX.x)
                rangeX.x = points[i].xy.x;
            if (points[i].xy.x > rangeX.y)
                rangeX.y = points[i].xy.x;
            if (points[i].xy.y < rangeY.x)
                rangeY.x = points[i].xy.y;
            if (points[i].xy.y > rangeY.y)
                rangeY.y = points[i].xy.y;
            Instantiate(cube3, new Vector3(points[i].xy.x, points[i].xy.y, 0f), Quaternion.identity, parent);
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
            bool isLeft = true;
            for (int j = 0; j < points[i].xy.weight; j++)
            {
                BucketNode node = new BucketNode();
                Point point = points[i];
                node.x = point.xy.x;
                if (!isLeft)
                {
                    node.yMax = point.rightNode.y - 1;
                    node.delta = 1f / ((point.rightNode.y - point.xy.y) / (point.rightNode.x - point.xy.x));
                }
                else
                {
                    isLeft = false;
                    if (point.xy.y <= point.leftNode.y)
                    {
                        node.yMax = point.leftNode.y - 1;
                        node.delta = 1f / ((point.leftNode.y - point.xy.y) / (point.leftNode.x - point.xy.x));
                    }
                    else
                    {
                        j--;
                        continue;
                    }
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
                int max = Mathf.FloorToInt(vaildList[j + 1].x); //左闭右开
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

}
