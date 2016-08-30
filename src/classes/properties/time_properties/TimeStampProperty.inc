<?php

/**
 * Class TimeStampProperty
 */
class TimeStampProperty extends TimeProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'           => 'timestamp',
        'default_schemas_fields' => array(
          'base'     => array(
            'description' => 'A UNIX timestamp.',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
          ),
          'revision' => array(
            'description' => 'A UNIX timestamp revision.',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
          ),
        ),
        'default_callbacks'      => array(
          'value' => 'request_time',
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}