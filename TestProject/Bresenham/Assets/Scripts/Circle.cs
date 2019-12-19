using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Circle : MonoBehaviour {

    public int r;
    public GameObject cube1;

	void Start () {
        int x, y, d;
        x = 0;
        y = r;
        d = 1 - r;

        while (x<=y)
        {
            Instantiate(cube1, new Vector2(x, y),Quaternion.identity);
            Instantiate(cube1, new Vector3(x, -y), Quaternion.identity);
            Instantiate(cube1, new Vector2(-x, -y), Quaternion.identity);
            Instantiate(cube1, new Vector3(-x, y), Quaternion.identity);
            Instantiate(cube1, new Vector2(y, x), Quaternion.identity);
            Instantiate(cube1, new Vector3(-y, x), Quaternion.identity);
            Instantiate(cube1, new Vector2(-y, -x), Quaternion.identity);
            Instantiate(cube1, new Vector3(y, -x), Quaternion.identity);


            if (d<0)
            {
                d += 2 * x + 3;
            }
            else
            {
                d += 2 * (x - y) + 5;
                y--;
            }
            x++;
        }
	}
}
