<?php

/**
 * Class MediumTextProperty
 */
class MediumTextProperty extends TextProperty {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'           => 'medium_text',
      ),
      $args
    );
    parent::__construct($args);
  }
}