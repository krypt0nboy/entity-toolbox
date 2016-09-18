<?php

/**
 * Class MenuItemModel
 */
class MenuItemModel extends MenuRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'structure' => array(
        'title'             => array(
          'type'   => 'string',
          'method' => 'buildTitle',
        ),
        'title callback'    => array(
          'type'   => 'string',
          'method' => 'buildTitleCallback',
        ),
        'title arguments'   => array(
          'type'   => 'array',
          'method' => 'buildTitleArguments',
        ),
        'description'       => array(
          'type'   => 'string',
          'method' => 'buildDescription',
        ),
        'page callback'     => array(
          'type'   => 'string',
          'method' => 'buildPageCallback',
        ),
        'page arguments'    => array(
          'type'   => 'array',
          'method' => 'buildPageArguments',
        ),
        'delivery callback' => array(
          'type'   => 'string',
          'method' => 'buildDeliveryCallback',
        ),
        'access callback'   => array(
          'type'   => 'string',
          'method' => 'buildAccessCallback',
        ),
        'access argument'   => array(
          'type'   => 'string',
          'method' => 'buildAccessArgument',
        ),
        'theme callback'    => array(
          'type'   => 'string',
          'method' => 'buildThemeCallback',
        ),
        'theme arguments'   => array(
          'type'   => 'array',
          'method' => 'buildThemeArguments',
        ),
        'file'              => array(
          'type'   => 'string',
          'method' => 'buildFile',
        ),
        'file path'         => array(
          'type'   => 'string',
          'method' => 'buildFilePath',
        ),
        'load arguments'    => array(
          'type'   => 'array',
          'method' => 'buildLoadArguments',
        ),
        'weight'            => array(
          'type'   => 'integer',
          'method' => 'buildWeight',
        ),
        'menu_name'         => array(
          'type'   => 'string',
          'method' => 'buildMenuName',
        ),
        'expanded'          => array(
          'type'   => 'string',
          'method' => 'buildExpanded',
        ),
        'context'           => array(
          'type'   => 'string',
          'method' => 'buildContext',
        ),
        'tab_parent'        => array(
          'type'   => 'string',
          'method' => 'buildTabParent',
        ),
        'tab_root'          => array(
          'type'   => 'string',
          'method' => 'buildTabRoot',
        ),
        'position'          => array(
          'type'   => 'string',
          'method' => 'buildPosition',
        ),
        'type'              => array(
          'type'   => 'integer',
          'method' => 'buildType',
        ),
        'options'           => array(
          'type'   => 'array',
          'method' => 'buildOptions',
        ),
      )
    ), $args);
    parent::__construct($args);
  }
}