using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playerMovement : MonoBehaviour
{
    // Start is called before the first frame update
    private Rigidbody2D playerRB;
    [SerializeField] float movementSpeed = 5.0f;
    [SerializeField] Sprite forwardLeanSprite;
    [SerializeField] Sprite backwardLeanSprite;
    [SerializeField] Sprite horizontalLeanSprite;
    private Sprite idleSprite;
    void Start()
    {
        playerRB = this.GetComponent<Rigidbody2D>();
        idleSprite = GetComponent<SpriteRenderer>().sprite;
    }

    // Update is called once per frame
    void Update()
    {
        playerRB.velocity = (new Vector2(Input.GetAxisRaw("Horizontal"), Input.GetAxisRaw("Vertical"))  * movementSpeed * Time.deltaTime);

        if(playerRB.velocity.x != 0) {
            GetComponent<SpriteRenderer>().sprite = horizontalLeanSprite;
            if(playerRB.velocity.x < 0) {
                GetComponent<SpriteRenderer>().flipX = true;
            } else {
                GetComponent<SpriteRenderer>().flipX = false;
            }
        } else if (playerRB.velocity.y != 0) {
            if(playerRB.velocity.y > 0) {
            GetComponent<SpriteRenderer>().sprite = forwardLeanSprite;
            } else {
                GetComponent<SpriteRenderer>().sprite = backwardLeanSprite;
            }
        } else {
            GetComponent<SpriteRenderer>().sprite = idleSprite;
        }
    }
}
