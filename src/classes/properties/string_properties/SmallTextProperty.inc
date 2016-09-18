<?php

/**
 * Class SmallTextProperty
 */
class SmallTextProperty extends TextProperty {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type' => 'small_text',
      ),
      $args
    );
    parent::__construct($args);
  }
}