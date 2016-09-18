<?php

/**
 * Class EntityHumanNameProperty
 */
class EntityHumanNameProperty extends VarcharProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'        => 'entity_human_name',
        'default_name'        => 'name',
        'default_key'         => 'label',
        'default_label'       => 'Name',
        'default_description' => 'The %toolbox_info_entity_type% name.',
        'default_weight'              => -998
      ),
      $args
    );
    parent::__construct($args);
  }
}