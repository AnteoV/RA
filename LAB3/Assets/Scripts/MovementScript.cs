using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovementScript : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        Physics2D.gravity = new Vector2(0f, -20f);
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.UpArrow) || Input.GetKeyDown(KeyCode.W))
        {
            Physics2D.gravity = new Vector2(0f, 25f);
        }

        if (Input.GetKeyDown(KeyCode.DownArrow) || Input.GetKeyDown(KeyCode.S))
        {
            Physics2D.gravity = new Vector2(0f, -25f);
        }

        if (Input.GetKeyDown(KeyCode.RightArrow) || Input.GetKeyDown(KeyCode.D))
        {
            Physics2D.gravity = new Vector2(25f, 0f);
        }

        if (Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetKeyDown(KeyCode.A))
        {
            Physics2D.gravity = new Vector2(-25f, 0f);
        }
    }


    public void Death(Collider2D other)
    {
        StartCoroutine(DeathCoroutine(other));
    }

    public void Respawn(Collider2D other)
    {
        Physics2D.gravity = new Vector2(0f, -25f);
        other.gameObject.transform.position = new Vector3(-8f, -4f, 0f);
        other.gameObject.GetComponent<Rigidbody2D>().velocity = Vector3.zero;
        other.gameObject.GetComponent<Rigidbody2D>().angularVelocity = 0f;
        Color temp = other.gameObject.GetComponent<SpriteRenderer>().color;
        temp.a = 1f;
        other.gameObject.GetComponent<SpriteRenderer>().color = temp;
    }

    IEnumerator DeathCoroutine(Collider2D other) 
    {
        Rigidbody2D rb = other.GetComponent<Rigidbody2D>();
        rb.constraints = RigidbodyConstraints2D.FreezePosition;
        StartCoroutine(LerpAlpha(other));
        yield return new WaitForSeconds(1.2f);
        rb.constraints = RigidbodyConstraints2D.None;
        Respawn(other);
    }

    IEnumerator LerpAlpha(Collider2D other)
    {
        Color tmp;
        float timeElapsed = 0;
        while (timeElapsed < 1)
        {
            tmp = other.gameObject.GetComponent<SpriteRenderer>().color; 
            tmp.a = Mathf.Lerp(1, 0, timeElapsed / 1);
            other.gameObject.GetComponent<SpriteRenderer>().color = tmp;
            timeElapsed += Time.deltaTime;
            yield return null;
        }
        tmp = other.gameObject.GetComponent<SpriteRenderer>().color;
        tmp.a = 0f;
        other.gameObject.GetComponent<SpriteRenderer>().color = tmp;
    }
}
