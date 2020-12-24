using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    private float speed;
    private SpriteAnimation spriteAnimation;
    public Sprite[] spriteArray;
    private SpriteRenderer SpriteRenderer;

    // Start is called before the first frame update
    void Start()
    {
        speed = 1;
        spriteAnimation = new SpriteAnimation(spriteArray, SpriteRenderer);
    }

    // Update is called once per frame
    void FixedUpdate()
    {

        float horizontal = Input.GetAxis("Horizontal");
        float vertical = Input.GetAxis("Vertical");

        GetComponent<Rigidbody2D>().velocity = new Vector2(horizontal * speed, vertical * speed);

        Debug.Log("Entering function");
        spriteAnimation.UpdateSprite(false);
    }
}
