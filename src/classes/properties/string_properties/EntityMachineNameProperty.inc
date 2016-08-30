<?php

/**
 * Class EntityMachineNameProperty
 */
class EntityMachineNameProperty extends MachineNameProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'        => 'entity_machine_name',
        'default_callbacks'   => array(
          'options_list' => '%toolbox_info_entity_type%_get_types',
        ),
        'default_forms'       => array(
          'edit'   => array(
            'source' => '',
          ),
          'inline' => array(
            'source' => '',
          ),
        ),
        'default_value'       => array(
          'max length' => 32
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}