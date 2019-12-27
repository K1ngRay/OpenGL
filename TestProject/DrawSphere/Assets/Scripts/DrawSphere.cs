using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DrawSphere : MonoBehaviour
{

    public int xSegment = 50;
    public int ySegment = 50;
    public float radius = 1f;
    public GameObject prefab;

    private List<GameObject> cloneList = new List<GameObject>();
    private int i1;
    private int i2;
    private int j1;
    private int j2;
    private bool isOver1;
    private bool isOver2;
    private bool isTime1;
    private bool isTime2;


    private void Start()
    {
        i1 = 0;
        i2 = ySegment;
        j1 = 0;
        j2 = 0;
        isOver1 = false;
        isOver2 = false;
        isTime1 = true;
        isTime2 = true;
    }
    void Update()
    {
        if (isOver1&&isOver2)
        {
            isOver1 = false;
            isOver2 = false;
            for (int i = 0; i < cloneList.Count; i++)
            {
                Destroy(cloneList[i]);
            }
            cloneList.Clear();
        }
        if (isTime1&&!isOver1)
        {
            isTime1 = false;
            Invoke("DrawSphereLogic1", 0);
        }
        if (isTime2&&!isOver2)
        {
            isTime2 = false;
            Invoke("DrawSphereLogic2", 0);
        }

    }

    void DrawSphereLogic1()
    {
        isTime1 = true;
        float yPos = Mathf.Cos((float)i1 / (float)ySegment * Mathf.PI);
        float xPos = Mathf.Cos((float)j1 / (float)xSegment * 2.0f * Mathf.PI) * Mathf.Sin((float)i1 / (float)ySegment * Mathf.PI);
        float zPos = Mathf.Sin((float)j1 / (float)xSegment * 2.0f * Mathf.PI) * Mathf.Sin((float)i1 / (float)ySegment * Mathf.PI);

        GameObject obj = Instantiate(prefab, new Vector3(xPos, yPos, zPos) * radius, Quaternion.identity);
        cloneList.Add(obj);

        j1++;
        if (j1 > xSegment)
        {
            j1 = 0;
            i1++;
        }
        if (i1 > ySegment >> 1)
        {
            j1 = 0;
            i1 = 0;
            isOver1 = true;
        }
    }

    void DrawSphereLogic2()
    {
        isTime2 = true;
        float yPos = Mathf.Cos((float)i2 / (float)ySegment * Mathf.PI);
        float xPos = Mathf.Cos((float)j2 / (float)xSegment * 2.0f * Mathf.PI) * Mathf.Sin((float)i2 / (float)ySegment * Mathf.PI);
        float zPos = Mathf.Sin((float)j2 / (float)xSegment * 2.0f * Mathf.PI) * Mathf.Sin((float)i2 / (float)ySegment * Mathf.PI);

        GameObject obj = Instantiate(prefab, new Vector3(xPos, yPos, zPos) * radius, Quaternion.identity);
        cloneList.Add(obj);

        j2++;
        if (j2 > xSegment)
        {
            j2 = 0;
            i2--;
            print(i2);
        }
        if (i2 <= ySegment >> 1)
        {
            j2 = 0;
            i2 = ySegment;
            isOver2 = true;
        }
    }

}
