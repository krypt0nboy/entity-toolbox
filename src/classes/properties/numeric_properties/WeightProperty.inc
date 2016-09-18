<?php

/**
 * Class WeightProperty
 */
class WeightProperty extends IntegerProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'default_type'                => 'weight',
      'default_name'                => 'weight',
      'default_label'               => 'Weight',
      'default_schemas_fields_name' => array(
        'base'              => 'weight',
        'revision'          => 'weight',
        'relation'          => 'weight',
        'relation_revision' => 'weight',
      ),
      'default_schemas_fields'      => array(
        'base'              => array(
          'type'     => 'int',
          'not null' => TRUE,
          'default'  => 0,
          'size'     => 'tiny',
        ),
        'revision'          => array(
          'type'     => 'int',
          'not null' => TRUE,
          'default'  => 0,
          'size'     => 'tiny',
        ),
        'relation'          => array(
          'type'     => 'int',
          'not null' => TRUE,
          'default'  => 0,
          'size'     => 'tiny',
        ),
        'relation_revision' => array(
          'type'     => 'int',
          'not null' => TRUE,
          'default'  => 0,
          'size'     => 'tiny',
        ),
      ),
      'default_weight'              => 0
    ), $args);
    parent::__construct($args);
  }
}

