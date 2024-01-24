using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovingBlockScript : MonoBehaviour
{

    public Vector2 pointA;
    public Vector2 pointB;
    private float speed;
    private float t;
    // Start is called before the first frame update
    void Start()
    {
        speed = 1;
    }

    // Update is called once per frame
    void Update()
    {
        t += Time.deltaTime * speed;
        transform.position = Vector2.Lerp(pointA, pointB, t);
        if (t >= 1)
        {
            var b = pointB;
            var a = pointA;
            pointA = b;
            pointB = a;
            t = 0;
        }
    }
}
