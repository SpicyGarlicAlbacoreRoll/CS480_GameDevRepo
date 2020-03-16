using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class backgroundCloudScript : MonoBehaviour
{
    // Start is called before the first frame update
    public float cloudSpeed = 5.0f;
    void Start()
    {
        transform.position = Camera.main.ViewportToWorldPoint(new Vector3(Random.Range(Camera.main.rect.xMin, Camera.main.rect.xMax), 1.5f, 0.0f));
        transform.position = new Vector3(transform.position.x, transform.position.y, 0.0f);
        transform.Rotate(0.0f, 0.0f, Random.Range(0.0f, 360.0f));
    }

    // Update is called once per frame
    void Update()
    {
        transform.position += Vector3.down * cloudSpeed * Time.deltaTime;
        if(Camera.main.WorldToViewportPoint(transform.position + Vector3.up * 10.0f).y < 0) {
            Destroy(this.gameObject);
        }
    }
}
