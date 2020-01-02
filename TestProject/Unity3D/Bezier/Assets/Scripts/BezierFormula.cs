using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class BezierFormula : MonoBehaviour
{
    public List<Transform> Points;
    public Transform line;
    public GameObject cube;
    public GameObject cube1;
    [Range(0,1)]
    public float step = 0.1f;

    private List<GameObject> GOList = new List<GameObject>();
    private List<Vector2> stepList = new List<Vector2>();   //记录递增的步长
    private List<Vector2> curPosList = new List<Vector2>(); //记录在每条边上当前的点

    // Update is called once per frame
    void Update()
    {
        StartCoroutine(InstantiateCor());
    }

    private void OnDrawGizmos()
    {
        DrawLine(Points, 0);
    }

    void BezierCurve()
    {
        curPosList.Clear();
        for (int i = 0; i < Points.Count; i++)
            curPosList.Add(Points[i].position);

        stepList.Clear();
        GetStepList(curPosList, stepList, 0);

        GOList.Add(Instantiate(cube, Points[0].position, Quaternion.identity, line));
        int stepIndex = 0;

        while (stepIndex != step)
        {
            stepIndex++;
            Vector2 newPos = GetBezierPoint(stepList, curPosList, stepIndex);
            GOList.Add(Instantiate(cube, newPos, Quaternion.identity, line));
        }
    }

    IEnumerator InstantiateCor()
    {
        for (int i = 0; i < GOList.Count; i++)
        {
            Destroy(GOList[i]);
        }
        GOList.Clear();
        yield return null;
        BezierCurve();
    }

    void DrawLine(List<Transform> points, int index)
    {
        if (index >= points.Count - 1)
        {
            return;
        }
        Debug.DrawLine(points[index].position, points[index + 1].position, Color.blue);
        DrawLine(points, index + 1);
    }

    /// <summary>
    /// 获取每条边的步长
    /// </summary>
    /// <param name="points"></param>
    /// <param name="list"></param>
    /// <param name="index"></param>
    void GetStepList(List<Vector2> points, List<Vector2> list, int index)
    {
        if (index >= points.Count - 1) return;
        Vector2 _step = new Vector2((points[index + 1].x - points[index].x) / step,
            (points[index + 1].y - points[index].y) / step);
        list.Add(_step);
        GetStepList(points, list, index + 1);
    }

    Vector2 GetBezierPoint(List<Vector2> stepList, List<Vector2> posList, int stepIndex)
    {
        Vector2 pos = Vector2.zero;
        List<Vector2> _stepList = new List<Vector2>();
        List<Vector2> _posList = new List<Vector2>();
        for (int i = 0; i < posList.Count - 1; i++)
        {
            posList[i] += stepList[i]; //递增
        }
        if (posList.Count <= 2)   //当只有三个点时，便可得出一个曲线点
        {
            Vector2 newStep = new Vector2((posList[1].x - posList[0].x) * stepIndex / this.step, (posList[1].y - posList[0].y) * stepIndex / this.step);
            pos = posList[0] + newStep;
            return pos;
        }
        else
        {
            for (int i = 0; i < posList.Count - 1; i++) //替换固定点
            {
                _posList.Add(posList[i]);
                GOList.Add(Instantiate(cube1, _posList[i], Quaternion.identity, line));
            }
            GetStepList(_posList, _stepList, 0); //重新计算步长
            for (int i = 0; i < _stepList.Count; i++)
            {
                _stepList[i] *= stepIndex;
            }
            return GetBezierPoint(_stepList, _posList, stepIndex);
        }
    }

}
