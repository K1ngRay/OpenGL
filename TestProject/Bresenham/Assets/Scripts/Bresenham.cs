using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class Bresenham : MonoBehaviour {

    public Transform cube1;
    public Transform cube2;
    public Transform cube3;

    [Header("Line")]
    public Vector2 oriVec2;
    public Vector2 FinVec2;

    private Transform curCube;
	void Start () {
        Func1();
        Func2();
        Func3();
        DrawBG();        
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

}
