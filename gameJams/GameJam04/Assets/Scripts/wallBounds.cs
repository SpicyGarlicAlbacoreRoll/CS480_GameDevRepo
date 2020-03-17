using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class wallBounds : MonoBehaviour
{

    public enum Walls
    {
        LEFT,
        RIGHT,
        TOP,
        BOTTOM
    }

    [SerializeField] public Walls wallPos;
    // Start is called before the first frame update
    void Start()
    {
        var offset = Vector3.zero;
        var boundingBoxOffset = Vector3.zero;
        switch(wallPos) {
            case (Walls.LEFT):
                offset = new Vector3(0.0f, Screen.height / 2, 0.0f);
                boundingBoxOffset = Vector3.left * GetComponent<BoxCollider2D>().bounds.extents.x;
                // Camera.main.ScreenToWorldPoint(new Vector3(0.0f, Screen.height / 2, 0.0f));
                break;
            case (Walls.RIGHT):
                boundingBoxOffset = Vector3.right * GetComponent<BoxCollider2D>().bounds.extents.x;
                offset = new Vector3(Screen.width, Screen.height / 2, 0.0f);
                break;
            case (Walls.BOTTOM):
                boundingBoxOffset = Vector3.down * GetComponent<BoxCollider2D>().bounds.extents.y;
                offset = new Vector3(Screen.width / 2, 0.0f, 0.0f);
                break;
            case (Walls.TOP):
                boundingBoxOffset = Vector3.up * GetComponent<BoxCollider2D>().bounds.extents.y;
                offset = new Vector3(Screen.width / 2, Screen.height, 0.0f);
                break;
        }

        transform.position = Camera.main.ScreenToWorldPoint(offset) + boundingBoxOffset;;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
