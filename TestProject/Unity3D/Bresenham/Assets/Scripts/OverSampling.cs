using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class OverSampling : MonoBehaviour {

    public Vector2Int32 oriPoint;
    public Vector2Int32 finPoint;
    public GameObject cube1;

	void Start () {
        int d, upIncre, downIncre;
        Vector2Int32 curPoint;
        Vector2Int32 delta;
        if (oriPoint.x>finPoint.x)
        {
            curPoint.x = oriPoint.x;
            oriPoint.x = finPoint.x;
            finPoint.x = curPoint.x;
            curPoint.y = oriPoint.y;
            oriPoint.y = finPoint.y;
            finPoint.y = curPoint.y;
        }
        curPoint = oriPoint;
        delta = new Vector2Int32(finPoint.x - oriPoint.x, finPoint.y - oriPoint.y);
        d = delta.x - 2 * delta.y; //Bresenham中点直线绘制算法的初值
        upIncre = 2 * delta.x - 2 * delta.y; //d<0时的d的增量
        downIncre = -2 * delta.y;   //d>=0时，d的增量
        while (curPoint.x <= finPoint.x)
        {
            float level = GetLevel(oriPoint, finPoint, curPoint);
            GameObject go = Instantiate(cube1, new Vector2(curPoint.x, curPoint.y), Quaternion.identity);
            go.GetComponent<MeshRenderer>().material.color = new Color(1f, 0.5f-level, 0.5f-level, 1f);

            curPoint.x++;
            if (d<0)
            {
                curPoint.y++;
                d += upIncre;
            }
            else
            {
                d += downIncre;
            }
        }
    }

    float GetLevel(Vector2Int32 ori,Vector2Int32 fin,Vector2Int32 des)
    {
        float level = 0;
        float k = (float)(fin.y - ori.y) / (float)(fin.x - ori.x);
        float b = fin.y - k * fin.x;
        level += GetSurLevel(des, k, b, Direction._1, ori, fin);
        level += GetSurLevel(des, k, b, Direction._2, ori, fin);
        level += GetSurLevel(des, k, b, Direction._3, ori, fin);
        level += GetSurLevel(des, k, b, Direction._4, ori, fin);
        return level/8f;
    }
    
    int GetSurLevel(Vector2Int32 des,float k,float b,Direction direction, Vector2Int32 ori, Vector2Int32 fin)
    {
        int level = 0;
        float x1 = 0f;
        float y1 = 0f;
        if (k>0)
        {
            switch (direction)
            {
                case Direction._1:
                    x1 = des.x;
                    y1 = des.y + 0.5f;
                    break;
                case Direction._2:
                    x1 = des.x - 0.5f;
                    y1 = des.y + 0.5f;
                    break;
                case Direction._3:
                    x1 = des.x - 0.5f;
                    y1 = des.y;
                    break;
                case Direction._4:
                    x1 = des.x;
                    y1 = des.y;
                    break;
                default:
                    break;
            }
            float y = k * x1 + b;
            if (x1 >= ori.x && x1 <= fin.x && y < y1 && y >= y1 - 0.5f)
                level += 1;
        }
        else
        {
            switch (direction)
            {
                case Direction._1:
                    x1 = des.x + 0.5f;
                    y1 = des.y;
                    break;
                case Direction._2:
                    x1 = des.x - 0.5f;
                    y1 = des.y;
                    break;
                case Direction._3:
                    x1 = des.x - 0.5f;
                    y1 = des.y - 0.5f;
                    break;
                case Direction._4:
                    x1 = des.x + 0.5f;
                    y1 = des.y - 0.5f;
                    break;
                default:
                    break;
            }
            float y = k * x1 + b;
            if (y > y1 && y <= y1 + 0.5f)
                level += 1;
        }
        return level;
    }
    enum Direction
    {
        _1,
        _2,
        _3,
        _4
    }
    [Serializable]
    public struct Vector2Int32
    {
        public int x;
        public int y;

        public Vector2Int32(int x,int y)
        {
            this.x = x;
            this.y = y;
        }
    }
}
