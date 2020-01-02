/*
 * 目前还不知道怎么用，只是抄了代码，很多变量都不知道是什么意思
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AreaSamping : MonoBehaviour
{

    public Vector2 oriPos;
    public Vector2 finPos;
    public int I;
    public GameObject prefab;

    void Start()
    {
        AntialiasingLine(oriPos, finPos, I);
    }

    void AntialiasingLine(Vector2 oriPos, Vector2 finPos, int I)
    {
        Vector2 curPos = oriPos;
        Vector2 delta = new Vector2(finPos.x - oriPos.x, finPos.y - oriPos.y);
        int m, w, e;
        m = I * (int)delta.y / (int)delta.x;
        w = I - m;
        e = I / 2;
        SetPixel(curPos, m / 2);
        while ((int)curPos.x<(int)finPos.x)
        {
            curPos.x++;
            if (e<w)
            {
                e += m;
            }
            else
            {
                curPos.y++;
                e -= m;
            }
            SetPixel(curPos, e);
        }
    }

    void SetPixel(Vector2 pos,int color)
    {
        GameObject GO = Instantiate(prefab, pos, Quaternion.identity);
        GO.GetComponent<MeshRenderer>().material.color = new Color(1f, color / 4f, color / 4f, 1f);
    }
}