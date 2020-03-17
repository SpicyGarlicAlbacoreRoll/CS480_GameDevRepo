using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class onHit : MonoBehaviour
{
    public UnityEvent onHitEvent;
    // Start is called before the first frame update
    private void OnCollisionEnter2D(Collision2D other) {
        if(other.gameObject.tag == "cloud") {
            onHitEvent.Invoke();
        }
    }
}
