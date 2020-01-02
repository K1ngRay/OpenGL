using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Algorithm : MonoBehaviour
{

    public Vector2 startPos;
    public Vector2 endPos;
    public Rect window;

    private Vector2 mPoint1;
    private Vector2 mPoint2;
    void Start()
    {
        Liang_Barsky(startPos, endPos);
    }

    private void OnDrawGizmos()
    {
        Debug.DrawLine(startPos, endPos, Color.blue);

        Debug.DrawLine(new Vector2(window.x, window.y), new Vector2(window.x, window.y + window.height), Color.yellow);
        Debug.DrawLine(new Vector2(window.x, window.y), new Vector2(window.x + window.width, window.y), Color.yellow);
        Debug.DrawLine(new Vector2(window.x, window.y + window.height), new Vector2(window.x + window.width, window.y + window.height), Color.yellow);
        Debug.DrawLine(new Vector2(window.x + window.width, window.y), new Vector2(window.x + window.width, window.y + window.height), Color.yellow);

        Liang_Barsky(startPos, endPos);
        Gizmos.color = Color.red;
        Gizmos.DrawCube(mPoint1, Vector3.one * 0.1f);
        Gizmos.DrawCube(mPoint2, Vector3.one * 0.1f);
    }

    // Update is called once per frame

    void Liang_Barsky(Vector2 vStartPos, Vector2 vEndPos)
    {
        float[] p = new float[4];//p表示两点之间的矢量距离，左右下上
        float[] q = new float[4];//q表示两点与窗口的距离
        float[] u = new float[4];//u表示p与q比例

        //p表示两点之间的距离
        p[0] = vStartPos.x - vEndPos.x;
        p[1] = -p[0];
        p[2] = vStartPos.y - vEndPos.y;
        p[3] = -p[2];

        //q表示两点与窗口的距离
        q[0] = vStartPos.x - window.x;
        q[1] = window.x + window.width - vStartPos.x;
        q[2] = vStartPos.y - window.y;
        q[3] = window.y + window.height - vStartPos.y;

        List<float> Uones = new List<float>();
        List<float> Utwos = new List<float>();
        Uones.Add(0f);
        Utwos.Add(1f);
        for (int i = 0; i < 4; i++)
        {
            u[i] = q[i] / p[i];
            if (p[i] < 0) //同方向
            {
                Uones.Add(u[i]);
            }
            else if (p[i] > 0) //同方向
            {
                Utwos.Add(u[i]);
            }
        }

        float Uone = Max(Uones);
        float Utwo = Min(Utwos);
        mPoint1 = new Vector2(ParamEquation(vStartPos.x, vEndPos.x, Uone), ParamEquation(vStartPos.y, vEndPos.y, Uone));
        mPoint2 = new Vector2(ParamEquation(vStartPos.x, vEndPos.x, Utwo), ParamEquation(vStartPos.y, vEndPos.y, Utwo));
    }

    /// <summary>
    /// 参数方程
    /// </summary>
    float ParamEquation(float vStartParam, float vEndParam, float t)
    {
        float result = 0f;
        result = vStartParam + (vEndParam - vStartParam) * t;
        return result;
    }

    float Max(List<float> vList)
    {
        float result = float.MinValue;
        for (int i = 0; i < vList.Count; i++)
        {
            if (result < vList[i])
            {
                result = vList[i];
            }
        }
        return result;
    }

    float Min(List<float> vList)
    {
        float result = float.MaxValue;
        for (int i = 0; i < vList.Count; i++)
        {
            if (result > vList[i])
            {
                result = vList[i];
            }
        }
        return result;
    }

}
