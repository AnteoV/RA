using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TriggerScript : MonoBehaviour
{
    void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("Ball"))
        {
            MovementScript ms = other.collider.GetComponent<MovementScript>();
            ms.Death(other.collider);
        }
    }
}
