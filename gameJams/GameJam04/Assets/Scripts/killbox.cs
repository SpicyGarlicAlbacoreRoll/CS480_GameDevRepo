using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class killbox : MonoBehaviour
{
    // Start is called before the first frame update
    public UnityEvent deathEvent;
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnCollisionEnter2D(Collision2D other) {
        if(other.gameObject.tag == "Player") {
            // other.gameObject.transform.position = Vector3.zero;
            Destroy(other.gameObject);
            GetComponent<AudioSource>().Play();
            StartCoroutine("beginDeath");
            
            

        }
    }

    IEnumerator beginDeath() {
        yield return new WaitForSeconds(0.35f);
        deathEvent.Invoke();
    }
}
